#include "stdafx.h"
#include "Wood_Road.h"
namespace App {
	Wood_Road::Wood_Road() {}
	Wood_Road::~Wood_Road() {}
	bool Wood_Road::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Wood_Road.tkm", true);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void Wood_Road::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Wood_Road::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}