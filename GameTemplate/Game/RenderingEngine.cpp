#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;
	

	
	void RenderingEngine::Execute(RenderContext& rc)
	{
		
		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
		g_engine->ExecuteRender();
		
		m_renderobject.clear();
	}
	void RenderingEngine::Init()
	{
		
	}
}