#include "stdafx.h"
#include "Shrub.h"

Shrub::Shrub() {}
Shrub::~Shrub() {}

bool Shrub::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/bg/Shrub.tkm", true);
	//���W�A��]�A�傫����ݒ肷��B
	SetupTRS();

	return true;
}
void Shrub::Update()
{
	//���f���̍X�V�B
	m_modelRender.Update();
}
void Shrub::Render(RenderContext& rc)
{
	//���f�����X�V�B
	m_modelRender.Draw(rc);
}