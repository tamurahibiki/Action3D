#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;

	void RenderingEngine::Render2DDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_renderobject) {
			renderObj->OnRenderFont2D(rc);
		}
		for (auto& renderObj : m_renderobject) {
			renderObj->OnRenderSprite2D(rc);
		}
	}

	void RenderingEngine::ShadowMapDraw(RenderContext& rc)
	{
		Vector3 dir = { g_Light.GetDirectionLightDirection().x,g_Light.GetDirectionLightDirection().y,g_Light.GetDirectionLightDirection().z };
		m_shadowMapRender.Render(rc, dir, m_renderobject);
	}
	void RenderingEngine::CreateGBuffer()
	{
		// 深度テクスチャー書き込み用のレンダーターゲット
		m_gBuffer[enGBufferDepth].Create(
			1600,
			900,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
		// 法線テクスチャ書き込み用のレンダーターゲット
		m_gBuffer[enGBufferNormal].Create(
			1600,
			900,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);
		//メタリックスムーステクスチャ書き込み用のレンダーターゲット
		m_gBuffer[enGBufferMetallicSmooth].Create(
			1600,
			900,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);
	}
	void RenderingEngine::RenderGBuffer(RenderContext& rc)
	{
		RenderTarget* rts[]
		{
			&m_gBuffer[enGBufferDepth],         // 0番目のレンダリングターゲット
			&m_gBuffer[enGBufferNormal],         // 1番目のレンダリングターゲット
			&m_gBuffer[enGBufferMetallicSmooth]
		};
		
		rc.WaitUntilToPossibleSetRenderTargets(3, rts);
		rc.SetRenderTargets(3, rts);
		rc.ClearRenderTargetViews(3, rts);
		
		for (auto& model : m_renderobject)
		{
			model->OnRenderToGBuffer(rc);
		}
		rc.WaitUntilFinishDrawingToRenderTargets(3, rts);
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		g_Light.Update();
		m_modelRenderCB.m_light = g_Light.GetLight();
		m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
		
		// ゲームオブジェクトマネージャーの描画処理を呼び出す。
		g_engine->ExecuteRender();
		
		ShadowMapDraw(rc);

		RenderGBuffer(rc);
		
		m_postEffect->Render(rc);
	
		Render2DDraw(rc);
		m_renderobject.clear();
	}
	void RenderingEngine::Init()
	{
		m_postEffect = &g_postEffect;
		m_shadowMapRender.Init();
		CreateGBuffer();
		m_modelRenderCB.m_light = g_Light.GetLight();
		m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
	}
}