#include "stdafx.h"
#include "Rock_Big.h"

Rock_Big::Rock_Big() {}
Rock_Big::~Rock_Big() {}

bool Rock_Big::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/bg/Rock_Big.tkm", false);
	//���W�A��]�A�傫����ݒ肷��B
	SetupTRS();
	
	return true;
}
void Rock_Big::Update()
{
	//���f���̍X�V�B
	m_modelRender.Update();
}
void Rock_Big::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}