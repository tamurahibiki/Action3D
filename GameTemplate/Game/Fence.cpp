#include "stdafx.h"
#include "Fence.h"

namespace App {
	Fence::Fence() {}
	Fence::~Fence() {}

	bool Fence::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Fence.tkm", true,false);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void Fence::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Fence::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}