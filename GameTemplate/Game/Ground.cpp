#include "stdafx.h"
#include "Ground.h"

Ground::Ground() {}
Ground::~Ground() {}

bool Ground::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/bg/Graund.tkm",true);
	//���W�A��]�A�傫����ݒ肷��B
	SetupTRS();
	
	//�����蔻����쐬����B
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix());

	return true;
}
void Ground::Update()
{
	//���f���̍X�V�B
	m_modelRender.Update();
}
void Ground::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}