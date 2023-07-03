#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
	/// <summary>
	/// スクリーンスペースリフレクション
	/// </summary>
	/// <remark>
	/// レイマーチング法によるSSR。
	/// 反射が発生するのは、G-Bufferに書き込まれたSmoothパラメーターに依存する。
	/// Smoothが0.0のピクセルでは反射は発生しない。最も強い反射はsmoothの値が1.0のときとなる。
	/// </reamrk>
	class Ssr {
	public:
		/// <summary>
		/// 初期化。
		/// </summary>
		void Init();
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		/// <param name="mainRenderTarget">メインレンダリングターゲット</param>
		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);

		/// <summary>
		/// ポストエフェクトを実行した結果となるテクスチャを取得。
		/// </summary>
		/// <returns>
		/// ポストエフェクトの実行結果となるテクスチャ。
		/// </returns>
		Texture& GetResultTexture()
		{
			return m_finalRt.GetRenderTargetTexture();
		}

		void SsrSpriteDraw(RenderContext& rc)
		{
			m_reflectionSprite.Draw(rc);
		}
		GaussianBlur m_blur;					// ブラー
	private:
		/// <summary>
		/// GPUに転送するデータ構造体。
		/// </summary>
		struct SsrCb {
			Matrix mViewProjInv;				// ビュープロジェクション行列の逆行列。
			Matrix mViewProj;					// ビュープロジェクション行列。
			Vector3 cameraPosInWorld;			// ワールド座標系でのカメラの視点。
		};
		RenderTarget m_reflectionRt;			// 映り込みをを書きこむためのレンダリングターゲット。
		RenderTarget m_finalRt;					// 最終合成スプライト
		
		SsrCb m_ssrCb;							// GPUに転送するデータ。
		Sprite m_reflectionSprite;				// 映り込み画像を作成するためのスプライト
		Sprite m_finalSprite;					// 最終合成スプライト。
	};
	extern Ssr g_ssr;
}