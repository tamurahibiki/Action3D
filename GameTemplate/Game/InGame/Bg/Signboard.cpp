#include "stdafx.h"
#include "Signboard.h"
namespace App {
	Signboard::Signboard() {}
	Signboard::~Signboard() {}

	bool Signboard::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Signboard.tkm", false);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		//�����蔻����쐬����B
		m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
			m_modelRender.GetModel().GetWorldMatrix());
		return true;
	}
	void Signboard::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Signboard::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}