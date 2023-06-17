#pragma once
#include "LightALL.h"
#include "ShadowMapRender.h"
#include "PostEffect.h"

namespace nsK2EngineLow 
{
	struct ModelRenderCB
	{
	public:
		Light m_light;          // ���C�g
		Matrix mlvp; // ���C�g�r���[�v���W�F�N�V�����s��B
		float ObjectCameraLength; //�f�B�U�����O�ŕK�v�Ȃ�B
	};
	class RenderingEngine : public Noncopyable
	{
	public:
		void Init();
		
		void AddRenderObject(IRenderer* renderobj)
		{
			m_renderobject.push_back(renderobj);
		}

		void CreateGBuffer();

		void Render2DDraw(RenderContext& rc);

		void ShadowMapDraw(RenderContext& rc);

		void Execute(RenderContext& rc);
		
		Texture& GetShadowMap()
		{
			return m_shadowMapRender.GetShadowMap();
		}
		Camera& GetLightCamera()
		{
			return m_shadowMapRender.GetLightCamera();
		}

		ModelRenderCB& GetModelRenderCB()
		{
			return m_modelRenderCB;
		}
		Texture& GetGBufferDepth()
		{
			return m_gBuffer[enGBufferDepth].GetRenderTargetTexture();
		}
		Texture& GetGBufferNormal()
		{
			return m_gBuffer[enGBufferNormal].GetRenderTargetTexture();
		}
		Texture& GetGBufferMetallicSmooth()
		{
			return m_gBuffer[enGBufferMetallicSmooth].GetRenderTargetTexture();
		}

	private:
		/// <summary>
		/// G-Buffer�̕`��
		/// </summary>
		/// <remark>
		/// ���̕`��G���W���̓t�H���[�h�����_�����O�Ȃ̂����A
		/// �|�X�g�G�t�F�N�g�Ŗ@���e�N�X�`����[�x�e�N�X�`���Ȃǂ𗘗p���邽�߁A
		/// G-Buffer�̍쐬���s���Ă���B
		/// </remark>
		void RenderGBuffer(RenderContext& rc);

		enum EnGBuffer
		{
			enGBufferDepth,	// 0
			enGBufferNormal,// 1
			enGBufferMetallicSmooth,//2
			enGBufferNum,	// 3
		};

	private:
		std::vector<IRenderer*> m_renderobject;
		ShadowMapRender m_shadowMapRender;
		PostEffect* m_postEffect = &g_postEffect;
		ModelRenderCB m_modelRenderCB;
		RenderTarget m_gBuffer[enGBufferNum];
	};
	extern RenderingEngine g_renderingEngine;
}

