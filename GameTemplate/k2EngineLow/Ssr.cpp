#include "k2EngineLowPreCompile.h"
#include "Ssr.h"

namespace nsK2EngineLow {

	Ssr g_ssr;

	void Ssr::Init()
	{
		{
			// 映り込み画像を作成するためのスプライトを作成。
			UINT w = g_postEffect.mainRenderTarget.GetWidth();
			UINT h = g_postEffect.mainRenderTarget.GetHeight();
			SpriteInitData initData;
			initData.m_width = w;
			initData.m_height = h;
			initData.m_fxFilePath = "Assets/shader/ssr.fx";
			initData.m_vsEntryPointFunc = "VSMain";
			initData.m_psEntryPoinFunc = "PSMain";
			initData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
			initData.m_textures[1] = &g_renderingEngine.GetGBufferDepth();
			initData.m_textures[2] = &g_renderingEngine.GetGBufferNormal();
			initData.m_textures[3] = &g_renderingEngine.GetGBufferMetallicSmooth();
			initData.m_expandConstantBuffer = &m_ssrCb;
			initData.m_expandConstantBufferSize = sizeof(SsrCb);

			initData.m_alphaBlendMode = AlphaBlendMode_None;
			initData.m_colorBufferFormat[0] = g_postEffect.mainRenderTarget.GetColorBufferFormat();
			initData.textureAddressMode = D3D12_TEXTURE_ADDRESS_MODE_BORDER;

			m_reflectionSprite.Init(initData);

			// αを映り込みの強さとして扱う。0.0なら映り込みなし、1.0が最も強く映り込みします。
			// αは0.0で初期化します。
			float clearColor[] = {
				0.0f, 0.0f, 0.0f, 0.0f
			};
			// 映り込み画像を描画するためのレンダリングターゲットを作成。
			m_reflectionRt.Create(
				w,
				h,
				1,
				1,
				g_postEffect.mainRenderTarget.GetColorBufferFormat(),
				DXGI_FORMAT_UNKNOWN,
				clearColor
			);
		}
		m_blur.Init(&m_reflectionRt.GetRenderTargetTexture(), false);
		{
			// 最終合成用のスプライトを初期化する
			SpriteInitData initData;
			initData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
			initData.m_textures[1] = &m_blur.GetBokeTexture();

			// 解像度はmainRenderTargetの幅と高さ
			initData.m_width = g_postEffect.mainRenderTarget.GetWidth();
			initData.m_height = g_postEffect.mainRenderTarget.GetHeight();
			// 2D用のシェーダーを使用する
			initData.m_fxFilePath = "Assets/shader/ssr.fx";
			initData.m_vsEntryPointFunc = "VSMain";
			initData.m_psEntryPoinFunc = "PSFinal";

			initData.m_alphaBlendMode = AlphaBlendMode_None;
			initData.m_colorBufferFormat[0] = g_postEffect.mainRenderTarget.GetColorBufferFormat();

			m_finalSprite.Init(initData);

			m_finalRt.Create(
				g_postEffect.mainRenderTarget.GetWidth(),
				g_postEffect.mainRenderTarget.GetHeight(),
				1,
				1,
				g_postEffect.mainRenderTarget.GetColorBufferFormat(),
				DXGI_FORMAT_UNKNOWN
			);
		}
	}

	void Ssr::Render(RenderContext& rc, RenderTarget& rt)
	{
		
		// まずは映り込みイメージを作成する。
		// レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_reflectionRt);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_reflectionRt);
		rc.ClearRenderTargetView(m_reflectionRt);

		m_ssrCb.cameraPosInWorld = g_camera3D->GetPosition();
		m_ssrCb.mViewProj = g_camera3D->GetViewProjectionMatrix();
		m_ssrCb.mViewProjInv.Inverse(m_ssrCb.mViewProj);

		// 描画
		m_reflectionSprite.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_reflectionRt);

		// 映り込み画像をガウシアンブラーでぼかしてデノイズを行う。
		m_blur.ExecuteOnGPU(rc, 2.0f);

		// レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_finalRt);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_finalRt);
		// 映り込み画像とメインシーンを合成していく。
		m_finalSprite.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_finalRt);
	}
}