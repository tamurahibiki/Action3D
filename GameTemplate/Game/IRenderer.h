#pragma once

namespace nsK2EngineLow {

	class IRenderer:public Noncopyable{
	public:
		virtual void OnRenderShadowMap(
			RenderContext& rc,
			const Matrix& lvpMatrix
		)
		{

		}
		
		virtual void OnRender2D(RenderContext& rc)
		{

		}
		
		virtual bool IsShadowCaster() const
		{
			return false;
		}
	};
}

