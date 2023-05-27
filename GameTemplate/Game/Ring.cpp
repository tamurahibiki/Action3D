#include "stdafx.h"
#include "Ring.h"

namespace
{
	//���f������]������Z���x�B
	const float ADDROTATION = 12.0f;
}
namespace App {
	Ring::Ring() {}
	Ring::~Ring() {}

	bool Ring::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Ring.tkm", true, true);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void Ring::Update()
	{
		//��Ƀ��f����Z�������ɉ�]����悤�ɂ���B
		m_rotation.AddRotationDegZ(ADDROTATION);
		//��]��ݒ肷��B
		m_modelRender.SetRotation(m_rotation);
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Ring::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}