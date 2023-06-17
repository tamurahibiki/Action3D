#include "stdafx.h"
#include "Flower.h"
namespace
{
	const int SCALEMULTIPLICATION = 4; //��Z����傫��
}
namespace App {
	Flower::Flower() {}
	Flower::~Flower() {}

	bool Flower::Start()
	{
		//�A�j���[�V������ǂݍ��ށB
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Flower_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Flower.tkm", false, m_animClips, enAnimationCilp_Num);
		//���W�A��]�A�傫����ݒ肷��B
		m_scale *= SCALEMULTIPLICATION;
		SetupTRS();

		return true;
	}
	void Flower::Update()
	{
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.0f);
		//�ҋ@�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Flower::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}