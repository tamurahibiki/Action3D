#pragma once

/// <summary>
/// �^�C�g���N���X
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
		SpriteRender			m_spriteRender;					//�^�C�g���̉摜�B
		float					m_alpha = 0.0f;					//pressbutton�̃��l�B
		SpriteRender			m_pressButton;					//pressbutton�̉摜�B
		SoundSource* m_bgm = nullptr;			   //�T�E���h�B
		SoundList* m_soundlist = nullptr;          //�T�E���h���X�g
		Fade* m_fade = nullptr;	 		           //�t�F�[�h�B
		/// <summary>
		///�t�F�[�h�A�E�g�����B
		/// </summary>
		/// <returns>�t�F�[�h�A�E�g���Ȃ�true�B</returns>
		bool					m_isWaitFadeout = false;
	};
}