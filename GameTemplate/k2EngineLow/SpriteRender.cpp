#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"

namespace nsK2EngineLow {
	SpriteRender::SpriteRender()
	{

	}

	void SpriteRender::Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode)
	{
		SpriteInitData initData;
		initData.m_ddsFilePath[0] = filePath;
		initData.m_fxFilePath = "Assets/shader/sprite.fx";
		initData.m_width = static_cast<UINT>(w);
		initData.m_height = static_cast<UINT>(h);
		initData.m_alphaBlendMode = alphaBlendMode;
		initData.m_colorBufferFormat[0] = DXGI_FORMAT_R16G16B16A16_FLOAT;

		m_sprite.Init(initData);
		m_isInit = true;
	}

	void SpriteRender::Draw(RenderContext& rc)
	{
		g_renderingEngine.AddRenderObject(this);
	}
}