#include "stdafx.h"
#include "WoodenBox.h"

WoodenBox::WoodenBox() {}
WoodenBox::~WoodenBox(){}

bool WoodenBox::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/gimmick/WoodenBox.tkm", false);
	//���W�A��]�A�傫����ݒ肷��B
	SetupTRS();
	
	return true;
}
void WoodenBox::Update()
{
	//���f���̍X�V�B
	m_modelRender.Update();
}
void WoodenBox::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}