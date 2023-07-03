#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
	/// <summary>
	/// �X�N���[���X�y�[�X���t���N�V����
	/// </summary>
	/// <remark>
	/// ���C�}�[�`���O�@�ɂ��SSR�B
	/// ���˂���������̂́AG-Buffer�ɏ������܂ꂽSmooth�p�����[�^�[�Ɉˑ�����B
	/// Smooth��0.0�̃s�N�Z���ł͔��˂͔������Ȃ��B�ł��������˂�smooth�̒l��1.0�̂Ƃ��ƂȂ�B
	/// </reamrk>
	class Ssr {
	public:
		/// <summary>
		/// �������B
		/// </summary>
		void Init();
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="mainRenderTarget">���C�������_�����O�^�[�Q�b�g</param>
		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);

		/// <summary>
		/// �|�X�g�G�t�F�N�g�����s�������ʂƂȂ�e�N�X�`�����擾�B
		/// </summary>
		/// <returns>
		/// �|�X�g�G�t�F�N�g�̎��s���ʂƂȂ�e�N�X�`���B
		/// </returns>
		Texture& GetResultTexture()
		{
			return m_finalRt.GetRenderTargetTexture();
		}

		void SsrSpriteDraw(RenderContext& rc)
		{
			m_reflectionSprite.Draw(rc);
		}
		GaussianBlur m_blur;					// �u���[
	private:
		/// <summary>
		/// GPU�ɓ]������f�[�^�\���́B
		/// </summary>
		struct SsrCb {
			Matrix mViewProjInv;				// �r���[�v���W�F�N�V�����s��̋t�s��B
			Matrix mViewProj;					// �r���[�v���W�F�N�V�����s��B
			Vector3 cameraPosInWorld;			// ���[���h���W�n�ł̃J�����̎��_�B
		};
		RenderTarget m_reflectionRt;			// �f�荞�݂����������ނ��߂̃����_�����O�^�[�Q�b�g�B
		RenderTarget m_finalRt;					// �ŏI�����X�v���C�g
		
		SsrCb m_ssrCb;							// GPU�ɓ]������f�[�^�B
		Sprite m_reflectionSprite;				// �f�荞�݉摜���쐬���邽�߂̃X�v���C�g
		Sprite m_finalSprite;					// �ŏI�����X�v���C�g�B
	};
	extern Ssr g_ssr;
}