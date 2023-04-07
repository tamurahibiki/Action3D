#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow {
	Bloom g_bloom;

	void Bloom::Init()
	{
		InitLuminanceSprite();
		InitBlur();
		InitFinalSprite();
		InitSprite();

	}
	void Bloom::InitSprite()
	{
		//�X�v���C�g�̏������I�u�W�F�N�g���쐬����B
		SpriteInitData spriteInitData;
		//�e�N�X�`����mainRenderTarget�̃J���[�o�b�t�@�B
		spriteInitData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
		spriteInitData.m_width = 1600;
		spriteInitData.m_height = 900;
		//���m�N���p�̃V�F�[�_�[���w�肷��B
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		//�������I�u�W�F�N�g���g���āA�X�v���C�g������������B

		copyToFrameBufferSprite.Init(spriteInitData);
	}

	void Bloom::Draw(RenderContext& rc)
	{
		copyToFrameBufferSprite.Draw(rc);
	}
	void Bloom::InitLuminanceSprite()
	{
		//step-4 �P�x���o�p�̃X�v���C�g���������B
		//�����������쐬����B
		SpriteInitData luminanceSpriteInitData;
		//�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		//���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		//�X�v���C�g�̕��ƍ�����luminnceRenderTarget�Ɠ����B
		luminanceSpriteInitData.m_width = 1600;
		luminanceSpriteInitData.m_height = 900;
		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�B
		luminanceSpriteInitData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
		//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��B
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//�쐬�����������������ƂɃX�v���C�g������������B

		luminanceSprite.Init(luminanceSpriteInitData);
	}

	void Bloom::InitBlur()
	{
		//step-1 �K�E�V�A���u���[���������B

		//gaussianBlur[0]�͋P�x�e�N�X�`���ɃK�E�V�A���u���[��������B
		gaussianBlur[0].Init(&g_postEffect.luminnceRenderTarget.GetRenderTargetTexture());
		//gaussianBlur[1]��gaussianBlur[0]�̃e�N�X�`���ɃK�E�V�A���u���[��������B
		gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
		//gaussianBlur[2]��gaussianBlur[1]�̃e�N�X�`���ɃK�E�V�A���u���[��������B
		gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
		//gaussianBlur[3]��gaussianBlur[2]�̃e�N�X�`���ɃK�E�V�A���u���[��������B
		gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());
	}
	void Bloom::InitFinalSprite()
	{
		//step-2 �{�P�摜���������ď������ނ��߂̃X�v���C�g���������B
		//����������ݒ肷��B
		SpriteInitData finalSpriteInitData;
		//�y���ځz�{�P�e�N�X�`����4���w�肷��B
		finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();
		//�𑜓x��mainRenderTarget�̕��ƍ����B
		finalSpriteInitData.m_width = 1600;
		finalSpriteInitData.m_height = 900;
		//�y���ځz�{�P�摜����������K�v������̂ŁA2D�p�̃V�F�[�_�[�ł͂Ȃ��A��p�V�F�[�_�[���w��B
		finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		//�������A���Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�����Z�ɂ���B
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		//�J���[�o�b�t�@�̃t�H�[�}�b�g�͗�ɂ���āA32�r�b�g���������_�o�b�t�@�B
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//�������������ɉ��Z�����p�̃X�v���C�g������������B

		finalSprite.Init(finalSpriteInitData);
	}

	void Bloom::Blur(RenderContext& rc)
	{
		gaussianBlur[0].ExecuteOnGPU(rc, 10);
		gaussianBlur[1].ExecuteOnGPU(rc, 10);
		gaussianBlur[2].ExecuteOnGPU(rc, 10);
		gaussianBlur[3].ExecuteOnGPU(rc, 10);
	}
	void Bloom::Render(RenderContext& rc, RenderTarget& rt)
	{
		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂B
		rc.WaitUntilToPossibleSetRenderTarget(rt);
		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.SetRenderTargetAndViewport(rt);
		//�ŏI�����B
		finalSprite.Draw(rc);
		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(rt);
	}

}