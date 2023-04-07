#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;
	

	
	void RenderingEngine::Execute(RenderContext& rc)
	{
		
		// ゲームオブジェクトマネージャーの描画処理を呼び出す。
		g_engine->ExecuteRender();
		
		m_renderobject.clear();
	}
	void RenderingEngine::Init()
	{
		
	}
}