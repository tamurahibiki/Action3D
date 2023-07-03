#include "k2EngineLowPreCompile.h"
#include "Fxaa.h"

namespace nsK2EngineLow {
    Fxaa g_fxaa;

    void Fxaa::Init()
    {
        {
            //スプライトの初期化オブジェクトを作成する。
            SpriteInitData InitData;
            //テクスチャはmainRenderTargetのカラーバッファ。
            InitData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
            InitData.m_width = 1600;
            InitData.m_height = 900;
            //シェーダーを指定する。
            InitData.m_fxFilePath = "Assets/shader/fxaa.fx";
            InitData.m_vsEntryPointFunc = "VSMain";
            InitData.m_psEntryPoinFunc = "PSMain";
            InitData.m_alphaBlendMode = AlphaBlendMode_None;

            //描き込むレンダリングターゲットのフォーマットを指定する。
            InitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

            //解像度をGPUに送るための定数バッファを設定する。
            InitData.m_expandConstantBuffer = (void*)&m_cB;
            InitData.m_expandConstantBufferSize = sizeof(FaxxBuffer) +
                (16 - (sizeof(FaxxBuffer) % 16));
            //初期化オブジェクトを使って、スプライトを初期化する。
            m_copySprite.Init(InitData);

            m_copyRt.Create(
                g_postEffect.mainRenderTarget.GetWidth(),
                g_postEffect.mainRenderTarget.GetHeight(),
                1,
                1,
                g_postEffect.mainRenderTarget.GetColorBufferFormat(),
                DXGI_FORMAT_D32_FLOAT
            );
        }
        m_blur.Init(&m_copyRt.GetRenderTargetTexture(), false);
        {
            // 最終合成用のスプライトを初期化する
            SpriteInitData spriteInitData;
            spriteInitData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
        
            // 解像度はmainRenderTargetの幅と高さ
            spriteInitData.m_width = g_postEffect.mainRenderTarget.GetWidth();
            spriteInitData.m_height = g_postEffect.mainRenderTarget.GetHeight();

            // 2D用のシェーダーを使用する
            spriteInitData.m_fxFilePath = "Assets/shader/fxaa.fx";
            spriteInitData.m_vsEntryPointFunc = "VSMain";
            spriteInitData.m_psEntryPoinFunc = "PSMain";
            spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
            //描き込むレンダリングターゲットのフォーマットを指定する。
            spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
           
            m_finalSprite.Init(spriteInitData);
        }   
    }
    void Fxaa::Render(RenderContext& rc, RenderTarget& rt)
    {
        // １．FXAAをかけた絵を描画するためのレンダリングターゲット(m_fxaaRt)に切り替える。
        // レンダリングターゲットとして利用できるまで待つ
        rc.WaitUntilToPossibleSetRenderTarget(m_copyRt);
        // レンダリングターゲットを設定
        rc.SetRenderTargetAndViewport(m_copyRt);
        rc.ClearRenderTargetView(m_copyRt);
       
        // ２．mainRenderTargetをテクスチャとしてスプライトを描画（ここでアンチをかける）
        m_copySprite.Draw(rc);
        // レンダリングターゲットへの書き込み終了待ち
        rc.WaitUntilFinishDrawingToRenderTarget(m_copyRt);
        
        // ３．レンダリングターゲットをmainRenderTargetに切り替える。
        // レンダリングターゲットとして利用できるまで待つ
        rc.WaitUntilToPossibleSetRenderTarget(g_postEffect.mainRenderTarget);
        // レンダリングターゲットを設定
        rc.SetRenderTargetAndViewport(g_postEffect.mainRenderTarget);

        // ４．m_fxaaRtをテクスチャとしてスプライトを描画(ここでmainRenderTargetに書き込まれる）
        // 描画
        m_finalSprite.Draw(rc);
        // レンダリングターゲットへの書き込み終了待ち
        rc.WaitUntilFinishDrawingToRenderTarget(g_postEffect.mainRenderTarget);
        // つまり、スプライトは2つ必要（２と４の描画のため）。
        //それらのスプライトで使用するテクスチャをちゃんと考える。
    }
}