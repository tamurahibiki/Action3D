#include "stdafx.h"
#include "GroundRoad.h"
namespace App {
	GroundRoad::GroundRoad() {}
	GroundRoad::~GroundRoad() {}

	bool GroundRoad::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/GroundRoad.tkm", true, false);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void GroundRoad::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void GroundRoad::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}