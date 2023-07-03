#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
    /// <summary>
    /// FXAA�B
    /// </summary>
    class Fxaa
    {
    public:
        /// <summary>
        /// �������B
        /// </summary>
        /// <param name="mainRenderTarget">���C�������_�[�^�[�Q�b�g�B</param>
        void Init();
        /// <summary>
        /// �`��B
        /// </summary>
        /// <param name="rc">�����_�\�R���e�L�X�g�B</param>
        /// <param name="mainRenderTarget">���C�������_�\�^�[�Q�b�g�B</param>
        void Render(RenderContext& rc, RenderTarget& rt);
        /// <summary>
        /// �|�X�g�G�t�F�N�g�����s�������ʂƂȂ�e�N�X�`�����擾�B
        /// </summary>
        /// <returns></returns>
        Texture& GetResultTexture()
        {
            return m_fxaaRt.GetRenderTargetTexture();
        }

        GaussianBlur m_blur;					// �u���[
    private:
        struct FaxxBuffer
        {
            float bufferW;
            float bufferH;
        };
        RenderTarget m_fxaaRt;  // FXAA���s�������_�����O�^�[�Q�b�g�B
        RenderTarget m_copyRt;
        Sprite m_finalSprite;	// �ŏI�����p�̃X�v���C�g
        Sprite m_copySprite;    //�@
        FaxxBuffer m_cB;        // �𑜓x��GPU�ɑ��邽�߂̒萔�o�b�t�@�\�B
       
    };
    extern Fxaa g_fxaa;
}

