#include "stdafx.h"
#include "HitBox.h"

HitBox::HitBox() {}
HitBox::~HitBox() {}

bool HitBox::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Box.tkm", true);
	//���W�A��]�A�傫����ݒ肷��B
	SetupTRS();
	
	//�����蔻����쐬����B
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix());
	return true;
}
void HitBox::Update()
{
	//���f���̍X�V�B
	m_modelRender.Update();
}