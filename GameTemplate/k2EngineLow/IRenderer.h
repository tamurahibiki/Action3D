#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// �����_�[���[�̊��N���X�B
	/// </summary>
	class IRenderer : public Noncopyable {
	public:
		/// <summary>
		/// �V���h�E�}�b�v�ւ̕`��p�X����Ă΂�鏈���B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="ligNo">���C�g�ԍ�</param>
		/// <param name="lvpMatrix">���C�g�r���[�v���W�F�N�V�����s��</param>
		virtual void OnRenderShadowMap(
			RenderContext& rc,
			const Matrix& lvpMatrix
		)
		{

		}
		/// <summary>
		/// �t�H���g�`��B
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRenderFont2D(RenderContext& rc)
		{

		}
		/// <summary>
		/// �X�v���C�g�`��B
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRenderSprite2D(RenderContext& rc)
		{

		}
		/// <summary>
		/// �V���h�E�L���X�^�[�H
		/// </summary>
		/// <returns>true���A���Ă���ƃV���h�E�L���X�^�[</returns>
		virtual bool IsShadowCaster() const
		{
			return false;
		}
	};
}
