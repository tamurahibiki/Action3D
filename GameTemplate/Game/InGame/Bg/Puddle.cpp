#include "stdafx.h"
#include "Puddle.h"
namespace App {
	Puddle::Puddle() {}
	Puddle::~Puddle() {}

	bool Puddle::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Puddle.tkm", true);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void Puddle::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Puddle::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}