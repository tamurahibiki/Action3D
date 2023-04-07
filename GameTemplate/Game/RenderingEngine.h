#pragma once


namespace nsK2EngineLow {
    class RenderingEngine : public Noncopyable
    {
    public:
        void Init();
		void AddRenderObject(IRenderer* renderobj)
		{
			m_renderobject.push_back(renderobj);
		}

		

		void Execute(RenderContext& rc);

		
		
	private:
		std::vector<IRenderer*> m_renderobject;
		RenderTarget m_mainRenderTarget;
		
	};

	extern RenderingEngine g_renderingEngine;
        
}