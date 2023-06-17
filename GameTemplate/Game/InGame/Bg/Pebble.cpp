#include "stdafx.h"
#include "Pebble.h"
#include "InGame/Player/Player.h"

namespace
{
	const float SEARCHRANGE = 200.0f;       //�T���͈�
	const float PEBBLEVISION = 360.0f;      //����
	const float FIRSTMULTIPLICATION = 5.0f; //�ŏ��ɏ�Z���鑬�x
	const float SECONDMULTIPLICATION = 4.0f;//���ɏ�Z���鑬�x
}
namespace App {
	Pebble::Pebble() {}
	Pebble::~Pebble() {}

	bool Pebble::Start()
	{
		//�A�j���[�V������ǂݍ��ށB
		m_animationClips[enAnimationClip_Idle].Load("Assets/animData/Pebble_Idle.tka");
		m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animationClips[enAnimationClip_Move].Load("Assets/animData/Pebble.tka");
		m_animationClips[enAnimationClip_Move].SetLoopFlag(false);

		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Pebble.tkm", false,m_animationClips, enAnimationClip_Num);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void Pebble::Update()
	{
		m_player = FindGO<Player>("player");

		//�X�e�[�g�̑J�ڏ����B
		ManageState();
		//�A�j���[�V�����̍Đ��B
		PlayAnimation();
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Pebble::Move()
	{
		//Z�����Ɉړ�������ݒ肷��B
		m_moveSpeed = Vector3::AxisZ;
		//���΂̈ړ����������߂���Ȃ�
		if (PebbleRot == true)
		{
			//�v���C���[�̉�]�Ə��΂̉�]�𓯂��ɂ���B
			m_playerrotation = m_player->GetRotation();
			//���΂̈ړ����������߂��Ȃ�����B
			PebbleRot = false;
		}
		//Z�����ɉ�]�B
		m_playerrotation.Apply(m_moveSpeed);
		//���W�̈ړ�
		m_position += m_moveSpeed * 5.0f;
		m_moveSpeed *= 4.0f;
		//���W���ړ�������B
		m_position += m_moveSpeed;
		//���W��ݒ肷��B
		m_modelRender.SetPosition(m_position);
	}
	const bool Pebble::SearchPlayer() const
	{
		//�v���C���[���珬�΂Ɍ������x�N�g�����v�Z����B
		Vector3 diff = m_player->GetPosition() - m_position;
		//�v���C���[�ɂ�����x�߂�������
		if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
		{
			//���΂���v���C���[�Ɍ������x�N�g���𐳋K������B
			diff.Normalize();
			/*���΂̐��ʂ̃x�N�g���ƁA���΂���v���C���[�Ɍ������x�N�g����
			����(cos��)�����߂�B*/
			float cos = m_forward.Dot(diff);
			//����(cos��)����p�x(��)�����߂�B
			float angle = acosf(cos);
			//�p�x(��)��360����菬�������
			if (angle <= (Math::PI / PEBBLEVISION) * PEBBLEVISION)
			{
				//�v���C���[��������B
				return true;
			}
		}
		//�v���C���[��������Ȃ��B
		return false;
	}
	void Pebble::ProcessCommonStateTransition()
	{
		//�����v���C���[�������Ă����Ȃ�
		if (SearchPlayer() == true)
		{
			//�ړ��X�e�[�g�ɑJ�ڂ���B
			m_pebbleState = enPebbleState_Move;
			return;
		}
		//�v���C���[��������Ȃ��Ȃ�
		else
		{
			//�ҋ@�X�e�[�g�ɑJ�ڂ���B
			m_pebbleState = enPebbleState_Idle;
		}
	}
	void Pebble::ProcessMoveStateTransition()
	{
		//�ړ������B
		Move();
		//�A�j���[�V�����̍Đ����I��������
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//���΂̈ړ����������߂���悤�ɂ���B
			PebbleRot = true;
			//���΂��폜����B
			DeleteGO(this);
		}
	}
	void Pebble::ManageState()
	{
		switch (m_pebbleState)
		{
			//�ҋ@�X�e�[�g�̎��B
		case enPebbleState_Idle:
			//���ʃX�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessCommonStateTransition();
			break;
			//�ړ��X�e�[�g�̎��B
		case enPebbleState_Move:
			//�ړ��X�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessMoveStateTransition();
			break;
		}
	}
	void Pebble::PlayAnimation()
	{
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.2f);
		switch (m_pebbleState)
		{
			//�ҋ@�X�e�[�g�̎��B
		case enPebbleState_Idle:
			//�ҋ@�A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//�ړ��X�e�[�g�̎��B
		case enPebbleState_Move:
			//�ړ��A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
			break;
		default:
			break;
		}
	}
	void Pebble::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}