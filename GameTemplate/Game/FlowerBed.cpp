#include "stdafx.h"
#include "FlowerBed.h"

namespace
{
	const float SCALEMULTIPLICATION = 2.5;//��Z����傫��
}
namespace App {
	FlowerBed::FlowerBed() {}
	FlowerBed::~FlowerBed() {}
	bool FlowerBed::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/FlowerBed.tkm", true,false );
		//���W�A��]�A�傫����ݒ肷��B
		m_scale *= SCALEMULTIPLICATION;
		SetupTRS();

		return true;
	}
	void FlowerBed::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void FlowerBed::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}