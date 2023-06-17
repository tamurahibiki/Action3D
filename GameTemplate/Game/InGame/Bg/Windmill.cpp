#include "stdafx.h"
#include "Windmill.h"
namespace App {
	Windmill::Windmill() {}
	Windmill::~Windmill() {}

	bool Windmill::Start()
	{
		//�A�j���[�V������ǂݍ��ށB
		m_animClips[enAnimationClip_Move].Load("Assets/animData/Windmill.tka");
		m_animClips[enAnimationClip_Move].SetLoopFlag(true);
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Windmill.tkm", false,m_animClips, enAnimationCilp_Num);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void Windmill::Update()
	{
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.0f);
		//��]�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Windmill::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}