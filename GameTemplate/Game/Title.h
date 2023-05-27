#pragma once

/// <summary>
/// タイトルクラス
/// </summary>
namespace App {
	class Fade;
	class SoundList;
	class Title : public IGameObject
	{
	public:
		Title();
		~Title();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	private:
		ModelRender m_modelRender;
		SpriteRender			m_spriteRender;					//タイトルの画像。
		float					m_alpha = 0.0f;					//pressbuttonのα値。
		SpriteRender			m_pressButton;					//pressbuttonの画像。
		SoundSource* m_bgm = nullptr;			   //サウンド。
		SoundList* m_soundlist = nullptr;          //サウンドリスト
		Fade* m_fade = nullptr;	 		           //フェード。
		/// <summary>
		///フェードアウト中か。
		/// </summary>
		/// <returns>フェードアウト中ならtrue。</returns>
		bool					m_isWaitFadeout = false;
	};
}