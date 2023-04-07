#include "stdafx.h"
#include "Player_Head.h"

namespace
{
	const float ROTADDITIONX = 60.0f;
	const float ROTADDITIONY = 90.0f;
	const float SCALEMULTIPLICATION = 0.5; //��Z����傫��
}

Player_Head::Player_Head() {}
Player_Head::~Player_Head() {}

bool Player_Head::Start()
{
	//�A�j���[�V������ǂݍ��ށB
	m_animClips[enAnimationClip_Idle].Load("Assets/animData/Player_Head.tka");
	m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/player/Player_Fort.tkm", false, m_animClips, enAnimationCilp_Num);
	//���W��ݒ肷��B
	m_modelRender.SetPosition(m_position);
	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);
	m_rotation.y += ROTADDITIONY;
	m_rotation.x += ROTADDITIONX;
	//�傫����ݒ肷��B
	m_modelRender.SetScale(m_scale* SCALEMULTIPLICATION);
	//���f�����X�V����B
	m_modelRender.Update();
	return true;
}
void Player_Head::Update()
{
	//�A�j���[�V�����̍Đ����x�B
	m_modelRender.SetAnimationSpeed(1.0f);
	//�ҋ@�A�j���[�V�������Đ��B
	m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.8f);
	//���f���̍X�V�����B
	m_modelRender.Update();
}
void Player_Head::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);
}