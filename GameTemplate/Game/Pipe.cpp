#include "stdafx.h"
#include "Pipe.h"

namespace App {
	Pipe::Pipe() {}
	Pipe::~Pipe() {}
	bool Pipe::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Pipe.tkm", true, false);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void Pipe::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Pipe::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}