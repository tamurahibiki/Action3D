#include "k2EngineLowPreCompile.h"
#include "PostEffect.h"

namespace nsK2EngineLow {

	PostEffect g_postEffect;


	void PostEffect::Init()
	{

		//step-1 �I�t�X�N���[���`��p�̃����_�����O�^�[�Q�b�g���쐬�B
		//RenderTarget�N���X�̃I�u�W�F�N�g���`�B

		//RenderTarget::Create()�𗘗p���āA�����_�����O�^�[�Q�b�g���쐬����B
		mainRenderTarget.Create(
			1600,												//�e�N�X�`���̕��B
			900,												//�e�N�X�`���̍����B
			1,													//Mipmap���x���B
			1,													//�e�N�X�`���z��̃T�C�Y�B
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT								//�f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
		);

		//�𑜓x�A�~�b�v�}�b�v���x��
		luminnceRenderTarget.Create(
			1600,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
			900,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
			1,
			1,
			//�y���ځz�J���[�o�b�t�@�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���B
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);	

		
	}
	void PostEffect::Render(RenderContext& rc)
	{
		
		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(g_postEffect.mainRenderTarget);

		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTarget(g_postEffect.mainRenderTarget);

		// �����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(g_postEffect.mainRenderTarget);

		g_engine->ExecuteRender();

		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(g_postEffect.mainRenderTarget);
		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(g_postEffect.luminnceRenderTarget);

		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTarget(g_postEffect.luminnceRenderTarget);
		// �����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(g_postEffect.luminnceRenderTarget);

		g_bloom.LuminanceSpriteDraw(rc);

		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(g_postEffect.luminnceRenderTarget);

		g_bloom.Blur(rc);
		g_bloom.Render(rc, g_postEffect.mainRenderTarget);

		// step-5 ��ʂɕ\������郌���_�����O�^�[�Q�b�g�ɖ߂�
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		g_bloom.Draw(rc);
		//�����ŃG�t�F�N�g�h���[�B
		EffectEngine::GetInstance()->Draw();

	}
}