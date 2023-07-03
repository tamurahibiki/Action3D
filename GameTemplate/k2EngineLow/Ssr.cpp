#include "k2EngineLowPreCompile.h"
#include "Ssr.h"

namespace nsK2EngineLow {

	Ssr g_ssr;

	void Ssr::Init()
	{
		{
			// �f�荞�݉摜���쐬���邽�߂̃X�v���C�g���쐬�B
			UINT w = g_postEffect.mainRenderTarget.GetWidth();
			UINT h = g_postEffect.mainRenderTarget.GetHeight();
			SpriteInitData initData;
			initData.m_width = w;
			initData.m_height = h;
			initData.m_fxFilePath = "Assets/shader/ssr.fx";
			initData.m_vsEntryPointFunc = "VSMain";
			initData.m_psEntryPoinFunc = "PSMain";
			initData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
			initData.m_textures[1] = &g_renderingEngine.GetGBufferDepth();
			initData.m_textures[2] = &g_renderingEngine.GetGBufferNormal();
			initData.m_textures[3] = &g_renderingEngine.GetGBufferMetallicSmooth();
			initData.m_expandConstantBuffer = &m_ssrCb;
			initData.m_expandConstantBufferSize = sizeof(SsrCb);

			initData.m_alphaBlendMode = AlphaBlendMode_None;
			initData.m_colorBufferFormat[0] = g_postEffect.mainRenderTarget.GetColorBufferFormat();
			initData.textureAddressMode = D3D12_TEXTURE_ADDRESS_MODE_BORDER;

			m_reflectionSprite.Init(initData);

			// �����f�荞�݂̋����Ƃ��Ĉ����B0.0�Ȃ�f�荞�݂Ȃ��A1.0���ł������f�荞�݂��܂��B
			// ����0.0�ŏ��������܂��B
			float clearColor[] = {
				0.0f, 0.0f, 0.0f, 0.0f
			};
			// �f�荞�݉摜��`�悷�邽�߂̃����_�����O�^�[�Q�b�g���쐬�B
			m_reflectionRt.Create(
				w,
				h,
				1,
				1,
				g_postEffect.mainRenderTarget.GetColorBufferFormat(),
				DXGI_FORMAT_UNKNOWN,
				clearColor
			);
		}
		m_blur.Init(&m_reflectionRt.GetRenderTargetTexture(), false);
		{
			// �ŏI�����p�̃X�v���C�g������������
			SpriteInitData initData;
			initData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
			initData.m_textures[1] = &m_blur.GetBokeTexture();

			// �𑜓x��mainRenderTarget�̕��ƍ���
			initData.m_width = g_postEffect.mainRenderTarget.GetWidth();
			initData.m_height = g_postEffect.mainRenderTarget.GetHeight();
			// 2D�p�̃V�F�[�_�[���g�p����
			initData.m_fxFilePath = "Assets/shader/ssr.fx";
			initData.m_vsEntryPointFunc = "VSMain";
			initData.m_psEntryPoinFunc = "PSFinal";

			initData.m_alphaBlendMode = AlphaBlendMode_None;
			initData.m_colorBufferFormat[0] = g_postEffect.mainRenderTarget.GetColorBufferFormat();

			m_finalSprite.Init(initData);

			m_finalRt.Create(
				g_postEffect.mainRenderTarget.GetWidth(),
				g_postEffect.mainRenderTarget.GetHeight(),
				1,
				1,
				g_postEffect.mainRenderTarget.GetColorBufferFormat(),
				DXGI_FORMAT_UNKNOWN
			);
		}
	}

	void Ssr::Render(RenderContext& rc, RenderTarget& rt)
	{
		
		// �܂��͉f�荞�݃C���[�W���쐬����B
		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_reflectionRt);
		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(m_reflectionRt);
		rc.ClearRenderTargetView(m_reflectionRt);

		m_ssrCb.cameraPosInWorld = g_camera3D->GetPosition();
		m_ssrCb.mViewProj = g_camera3D->GetViewProjectionMatrix();
		m_ssrCb.mViewProjInv.Inverse(m_ssrCb.mViewProj);

		// �`��
		m_reflectionSprite.Draw(rc);
		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_reflectionRt);

		// �f�荞�݉摜���K�E�V�A���u���[�łڂ����ăf�m�C�Y���s���B
		m_blur.ExecuteOnGPU(rc, 2.0f);

		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_finalRt);
		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(m_finalRt);
		// �f�荞�݉摜�ƃ��C���V�[�����������Ă����B
		m_finalSprite.Draw(rc);
		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_finalRt);
	}
}