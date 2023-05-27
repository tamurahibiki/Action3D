#include "stdafx.h"
#include "Bard.h"
#include "Player.h"
#include "SoundList.h"
namespace 
{
	const float  SEARCHRANGE          = 800.0f;//�T���͈�
	const float  BARDVISION           = 360.0f;//����
	const float  DISAPPEARTIMEMAX     = 4.0f;  //����������܂ł̎���
	const float  FIRSTMULTIPLICATION  = 10.0f; //�ŏ��ɏ�Z���鑬�x
	const float  SECONDMULTIPLICATION = 5.0f;  //���ɏ�Z���鑬�x
}
namespace App {
	Bard::Bard() {}
	Bard::~Bard() {}
	bool Bard::Start()
	{
		//�A�j���[�V������ǂݍ��ށB
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Bard_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animClips[enAnimationClip_Move].Load("Assets/animData/Bard_Move.tka");
		m_animClips[enAnimationClip_Move].SetLoopFlag(true);

		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Bard.tkm", false,false, m_animClips, enAnimationCilp_Num);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		m_soundlist = FindGO<SoundList>("soundlist");
		return true;
	}
	void Bard::Update()
	{
		m_player = FindGO<Player>("player");
		//�X�e�[�g�̑J�ڏ����B
		ManageState();
		//�A�j���[�V�����̍Đ��B
		PlayAnimation();
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Bard::Move()
	{
		//YZ�����Ɉړ�������ݒ肷��B
		m_moveSpeed = Vector3::AxisYZ;
		//YZ�����ɉ�]�B
		m_rotation.Apply(m_moveSpeed);
		//���W�̈ړ��B
		m_position += m_moveSpeed * FIRSTMULTIPLICATION;
		m_moveSpeed *= SECONDMULTIPLICATION;
		//���W���ړ�������B
		m_position += m_moveSpeed;
		//���W��ݒ肷��B
		m_modelRender.SetPosition(m_position);
	}
	const bool Bard::SearchPlayer() const
	{
		//�v���C���[���璹�Ɍ������x�N�g�����v�Z����B
		Vector3 diff = m_player->GetPosition() - m_position;
		//�v���C���[�ɂ�����x�߂�������
		if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
		{
			//������v���C���[�Ɍ������x�N�g���𐳋K������B
			diff.Normalize();
			/*���̐��ʂ̃x�N�g���ƁA������v���C���[�Ɍ������x�N�g����
			����(cos��)�����߂�B*/
			float cos = m_forward.Dot(diff);
			//����(cos��)����p�x(��)�����߂�B
			float angle = acosf(cos);
			//�p�x(��)��360����菬�������
			if (angle <= (Math::PI / BARDVISION) * BARDVISION)
			{
				//�v���C���[��������B
				return true;
			}
		}
		//�v���C���[��������Ȃ��B
		return false;
	}
	void Bard::ProcessCommonStateTransition()
	{
		//�����v���C���[�������Ă����Ȃ�
		if (SearchPlayer() == true)
		{
			//�ړ��X�e�[�g�ɑJ�ڂ���B
			m_bardState = enBardState_Move;
			return;
		}
		//�v���C���[��������Ȃ��Ȃ�
		else
		{
			//�ҋ@�X�e�[�g�ɑJ�ڂ���B
			m_bardState = enBardState_Idle;
		}
	}
	void Bard::ProcessMoveStateTransition()
	{
		//�H�΂���������x�����Đ�����B
		if (m_moveSound == true) {
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->BARDMOVE);
			se->Play(false);//���[�v�Đ������Ȃ��B
			se->SetVolume(0.15f);//�{�����[��
			m_moveSound = false;
		}
		//�ړ������B
		Move();
		//����������܂ł̎��Ԃ��J�E���g����B
		m_disappearTime += g_gameTime->GetFrameDeltaTime();
		//4�b�o��
		if (m_disappearTime > DISAPPEARTIMEMAX)
		{
			//���M���폜����B
			DeleteGO(this);
		}
	}
	void Bard::ManageState()
	{
		switch (m_bardState)
		{
			//�ҋ@�X�e�[�g�̎��B
		case enBardState_Idle:
			//���ʃX�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessCommonStateTransition();
			break;
			//�ړ��X�e�[�g�̎��B
		case enBardState_Move:
			//�ړ��X�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessMoveStateTransition();
			break;
		}
	}
	void Bard::PlayAnimation()
	{
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.2f);
		switch (m_bardState)
		{
			//�ҋ@�X�e�[�g�̎��B
		case enBardState_Idle:
			//�ҋ@�A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//�ړ��X�e�[�g�̎��B
		case enBardState_Move:
			//�ړ��A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
			break;
		default:
			break;
		}
	}
	void Bard::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}