#include "stdafx.h"
#include "Grass.h"

namespace
{
	const float SCALEMULTIPLICATION = 2.5;//��Z����傫��
}
namespace App {
	Grass::Grass() {}
	Grass::~Grass() {}

	bool Grass::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Grass.tkm", true, false);
		//���W�A��]�A�傫����ݒ肷��B
		m_scale *= SCALEMULTIPLICATION;
		SetupTRS();

		return true;
	}
	void Grass::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Grass::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}