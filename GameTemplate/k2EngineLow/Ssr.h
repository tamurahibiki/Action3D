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
	/// Smooth�̈����́A�{�G���W����PBR�̃��[�N�t���[���Q�ƁB
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
		/// �|�X�g�̌��ʂ̉摜�����C�������_�����O�^�[�Q�b�g�ɃR�s�[����H
		/// </summary>
		/// <returns>
		/// true��Ԃ��ƁAGetResultTexture()�֐����Ԃ��Ă���A
		/// �|�X�g�G�t�F�N�g�̌��ʂƂȂ�e�N�X�`�������C�������_�����O�^�[�Q�b�g�ɃR�s�[���܂��B
		/// OnRender()�֐��̒��ŁA���łɌ��ʂ����C�������_�����O�^�[�Q�b�g�ɏ������ݍς݂ł���Ȃ�A
		/// false��Ԃ��Ă��������B
		/// </returns>
		bool IsCopyResultTextureToMainRenderTarget() const
		{
			return true;
		}
		/// <summary>
		/// �|�X�g�G�t�F�N�g�����s�������ʂƂȂ�e�N�X�`�����擾�B
		/// </summary>
		/// <returns>
		/// �|�X�g�G�t�F�N�g�̎��s���ʂƂȂ�e�N�X�`���B
		/// IsCopyResultTextureToMainRenderTarget()�֐���true��Ԃ��ꍇ�A
		/// OnRender()�֐��̎��s��Ƀ��C�������_�����O�^�[�Q�b�g�ɁA���̃e�N�X�`���̓��e��
		/// �\��t�����܂��B
		/// IsCopyResultTextureToMainRenderTarget()�֐���false��Ԃ��ꍇ�́A
		/// �{�֐��͗��p����܂���B
		/// </returns>
		Texture& GetResultTexture()
		{
			return m_finalRt.GetRenderTargetTexture();
		}

		void SsrSpriteDraw(RenderContext& rc)
		{
			m_reflectionSprite.Draw(rc);
		}

		/// <summary>
		/// SSR��L���ɂ���B
		/// </summary>
		void Enable()
		{
			m_isEnable = true;
		}
		/// <summary>
		/// SSR�𖳌��ɂ���B
		/// </summary>
		void Disable()
		{
			m_isEnable = false;
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
		bool m_isEnable = true;					// SSR�̗L���A�����B
	};
	extern Ssr g_ssr;
}