#include "stdafx.h"
#include "Stairs.h"
namespace App {
	Stairs::Stairs() {}
	Stairs::~Stairs() {}

	bool Stairs::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Stairs.tkm", true);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void Stairs::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Stairs::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}