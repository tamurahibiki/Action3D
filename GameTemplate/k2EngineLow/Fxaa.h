#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
    /// <summary>
    /// FXAA。
    /// </summary>
    class Fxaa
    {
    public:
        /// <summary>
        /// 初期化。
        /// </summary>
        /// <param name="mainRenderTarget">メインレンダーターゲット。</param>
        void Init();
        /// <summary>
        /// 描画。
        /// </summary>
        /// <param name="rc">レンダ―コンテキスト。</param>
        /// <param name="mainRenderTarget">メインレンダ―ターゲット。</param>
        void Render(RenderContext& rc, RenderTarget& rt);
        /// <summary>
        /// ポストエフェクトを実行した結果となるテクスチャを取得。
        /// </summary>
        /// <returns></returns>
        Texture& GetResultTexture()
        {
            return m_fxaaRt.GetRenderTargetTexture();
        }

        GaussianBlur m_blur;					// ブラー
    private:
        struct FaxxBuffer
        {
            float bufferW;
            float bufferH;
        };
        RenderTarget m_fxaaRt;  // FXAAを行うレンダリングターゲット。
        RenderTarget m_copyRt;
        Sprite m_finalSprite;	// 最終合成用のスプライト
        Sprite m_copySprite;    //　
        FaxxBuffer m_cB;        // 解像度をGPUに送るための定数バッファ―。
       
    };
    extern Fxaa g_fxaa;
}

