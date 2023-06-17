#pragma once
#include "Ssr.h"
namespace nsK2EngineLow {
	class PostEffect
	{
	public:
		void Init();
		void Render(RenderContext& rc);
		RenderTarget mainRenderTarget;
		RenderTarget luminnceRenderTarget;
		//RenderTarget m_depthRT;
		//RenderTarget m_normalRT;
		Ssr m_ssr;
	};

	extern PostEffect g_postEffect;

}
