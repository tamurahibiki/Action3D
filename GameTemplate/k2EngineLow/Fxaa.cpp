#include "k2EngineLowPreCompile.h"
#include "Fxaa.h"

namespace nsK2EngineLow {
    Fxaa g_fxaa;

    void Fxaa::Init()
    {
        {
            //�X�v���C�g�̏������I�u�W�F�N�g���쐬����B
            SpriteInitData InitData;
            //�e�N�X�`����mainRenderTarget�̃J���[�o�b�t�@�B
            InitData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
            InitData.m_width = 1600;
            InitData.m_height = 900;
            //�V�F�[�_�[���w�肷��B
            InitData.m_fxFilePath = "Assets/shader/fxaa.fx";
            InitData.m_vsEntryPointFunc = "VSMain";
            InitData.m_psEntryPoinFunc = "PSMain";
            InitData.m_alphaBlendMode = AlphaBlendMode_None;

            //�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��B
            InitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

            //�𑜓x��GPU�ɑ��邽�߂̒萔�o�b�t�@��ݒ肷��B
            InitData.m_expandConstantBuffer = (void*)&m_cB;
            InitData.m_expandConstantBufferSize = sizeof(FaxxBuffer) +
                (16 - (sizeof(FaxxBuffer) % 16));
            //�������I�u�W�F�N�g���g���āA�X�v���C�g������������B
            m_copySprite.Init(InitData);

            m_copyRt.Create(
                g_postEffect.mainRenderTarget.GetWidth(),
                g_postEffect.mainRenderTarget.GetHeight(),
                1,
                1,
                g_postEffect.mainRenderTarget.GetColorBufferFormat(),
                DXGI_FORMAT_D32_FLOAT
            );
        }
        m_blur.Init(&m_copyRt.GetRenderTargetTexture(), false);
        {
            // �ŏI�����p�̃X�v���C�g������������
            SpriteInitData spriteInitData;
            spriteInitData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
        
            // �𑜓x��mainRenderTarget�̕��ƍ���
            spriteInitData.m_width = g_postEffect.mainRenderTarget.GetWidth();
            spriteInitData.m_height = g_postEffect.mainRenderTarget.GetHeight();

            // 2D�p�̃V�F�[�_�[���g�p����
            spriteInitData.m_fxFilePath = "Assets/shader/fxaa.fx";
            spriteInitData.m_vsEntryPointFunc = "VSMain";
            spriteInitData.m_psEntryPoinFunc = "PSMain";
            spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
            //�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��B
            spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
           
            m_finalSprite.Init(spriteInitData);
        }   
    }
    void Fxaa::Render(RenderContext& rc, RenderTarget& rt)
    {
        // �P�DFXAA���������G��`�悷�邽�߂̃����_�����O�^�[�Q�b�g(m_fxaaRt)�ɐ؂�ւ���B
        // �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
        rc.WaitUntilToPossibleSetRenderTarget(m_copyRt);
        // �����_�����O�^�[�Q�b�g��ݒ�
        rc.SetRenderTargetAndViewport(m_copyRt);
        rc.ClearRenderTargetView(m_copyRt);
       
        // �Q�DmainRenderTarget���e�N�X�`���Ƃ��ăX�v���C�g��`��i�����ŃA���`��������j
        m_copySprite.Draw(rc);
        // �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
        rc.WaitUntilFinishDrawingToRenderTarget(m_copyRt);
        
        // �R�D�����_�����O�^�[�Q�b�g��mainRenderTarget�ɐ؂�ւ���B
        // �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
        rc.WaitUntilToPossibleSetRenderTarget(g_postEffect.mainRenderTarget);
        // �����_�����O�^�[�Q�b�g��ݒ�
        rc.SetRenderTargetAndViewport(g_postEffect.mainRenderTarget);

        // �S�Dm_fxaaRt���e�N�X�`���Ƃ��ăX�v���C�g��`��(������mainRenderTarget�ɏ������܂��j
        // �`��
        m_finalSprite.Draw(rc);
        // �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
        rc.WaitUntilFinishDrawingToRenderTarget(g_postEffect.mainRenderTarget);
        // �܂�A�X�v���C�g��2�K�v�i�Q�ƂS�̕`��̂��߁j�B
        //�����̃X�v���C�g�Ŏg�p����e�N�X�`���������ƍl����B
    }
}