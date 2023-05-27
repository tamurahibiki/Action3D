#include "stdafx.h"
#include "Enemy_Green.h"
#include "Player.h"
#include "Shell.h"
#include "CollisionObject.h"
#include "SoundList.h"

namespace
{   const float  SCALEMULTIPLICATION = 1.5f;    //��Z����傫���B
	const float  SEARCHRANGE         = 3000.0f; //�T���͈�
	const float  GRRENVISION         = 180.0f;  //����
	const float  CHARACON            = 100.0f;  //�����蔻��̔��a�ƍ���
	const float  SHELLADDITIONY      = 180.0f;  //�C�e�ɉ��Z���鍂��
}
namespace App {
	Enemy_Green::Enemy_Green() {}
	Enemy_Green::~Enemy_Green() {}
	bool Enemy_Green::Start()
	{
		//�A�j���[�V������ǂݍ��ށB
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Enemy_Green_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animClips[enAnimationClip_Attack].Load("Assets/animData/Enemy_Green_Attack.tka");
		m_animClips[enAnimationClip_Attack].SetLoopFlag(false);
		m_animClips[enAnimationClip_Down].Load("Assets/animData/Enemy_Green_Down.tka");
		m_animClips[enAnimationClip_Down].SetLoopFlag(false);
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/enemy/Enemy_Green.tkm", false, false, m_animClips, enAnimationCilp_Num);
		//���W�A��]�A�傫����ݒ肷��B
		m_scale *= SCALEMULTIPLICATION;
		SetupTRS();

		//�����蔻����쐬����B
		m_charaCon.Init(
			CHARACON,//���a
			CHARACON,//����
			m_position//���W
		);
		//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
		m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
			OnAnimationEvent(clipName, eventName);
			});
		m_soundlist = FindGO<SoundList>("soundlist");

		return true;
	}
	void Enemy_Green::Update()
	{
		m_player = FindGO<Player>("player");
		//��]�����B
		Rotation();
		//�����蔻��B
		Collision();
		//�X�e�[�g�̑J�ڏ����B
		ManageState();
		//�A�j���[�V�����̍Đ��B
		PlayAnimation();
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Enemy_Green::Rotation()
	{
		EnemyRotation();
	}
	void Enemy_Green::MakeAttack()
	{
		//�C�e�̃I�u�W�F�N�g���쐬����B
		Shell* attack = NewGO<Shell>(0, "shell");
		//���W��ݒ肷��B
		Vector3 attackPosition = m_position;
		attackPosition.x += CHARACON;
		attackPosition.y += SHELLADDITIONY;
		attack->SetPosition(attackPosition);
		//��]��ݒ肷��B
		attack->SetRotation(m_rotation);
	}
	void Enemy_Green::Collision()
	{
		//�v���C���[�̑��̃R���W��������������B
		const auto& legcollision = g_collisionObjectManager->FindCollisionObjects("Leg");
		//�R���W�����̔z���for���ŉ񂷁B
		for (auto collision : legcollision)
		{
			//�v���C���[�̑��̃R���W�����Ǝ��g�̓����蔻�肪�Փ˂�����
			if (collision->IsHit(m_charaCon))
			{
				//���ݑ�W�����v���o����悤�ɂ���B
				m_player->JunpCount = true;
				//���܂ꂽ���ʉ�����x�����Đ�����B
				if (DownSound == true)
				{
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(m_soundlist->ENEMYDOWN2);
					se->Play(false);//���[�v�Đ����Ȃ��B
					se->SetVolume(0.05f);//�{�����[���̐ݒ�B
					DownSound = false;
				}
				return;
			}
			else
			{
				//�v���C���[�����ݑ�W�����v�o���Ȃ�������
				if (m_player->JunpCount == false)
				{
					//���܂ꂽ���ʉ����Đ��o����悤�ɂ���B
					DownSound = true;
				}
			}
		}
		//�v���C���[�̂��K�̃R���W��������������B
		const auto& hipcollision = g_collisionObjectManager->FindCollisionObjects("Hip");
		//�R���W�����̔z���for���ŉ񂷁B
		for (auto collision : hipcollision)
		{
			//�v���C���[�̂��K�̃R���W�����Ǝ��g�̓����蔻�肪�Փ˂�����
			if (collision->IsHit(m_charaCon))
			{
				//�|�ꂽ���ʉ�����x�����Đ�����B
				if (DownSound == true)
				{
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(m_soundlist->ENEMYDOWNHIP);
					se->Play(false);//���[�v�Đ����Ȃ��B
					se->SetVolume(0.2f);//�{�����[���̐ݒ�B
					DownSound = false;
				}
				//�_�E���X�e�[�g�ɑJ�ڂ���B
				m_EnemyState = enEnemyState_Down;
				return;
			}
		}
	}
	const bool Enemy_Green::SearchPlayer() const
	{
		//�v���C���[�����S���Ă��Ȃ��Ȃ�
		if (m_player->Dead == false)
		{
			//�v���C���[���牓�����U���G�l�~�[�Ɍ������x�N�g�����v�Z����
			Vector3 diff = m_player->GetPosition() - m_position;
			//�v���C���[�ɂ�����x�߂�������
			if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
			{
				//�������U���G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K������B
				diff.Normalize();
				/*�������U���G�l�~�[�̐��ʂ̃x�N�g���ƁA
				�������U���G�l�~�[����v���C���[�Ɍ������x�N�g����
				����(cos��)�����߂�B*/
				float cos = m_forward.Dot(diff);
				//����(cos��)����p�x(��)�����߂�B
				float angle = acosf(cos);
				//�p�x(��)��180����菬�������
				if (angle <= (Math::PI / GRRENVISION) * GRRENVISION)
				{
					//�v���C���[��������B
					return true;
				}
			}
			//�v���C���[��������Ȃ��B
			return false;
		}
	}
	void Enemy_Green::ProcessCommonStateTransition()
	{
		//�����v���C���[�������Ă����Ȃ�
		if (SearchPlayer() == true)
		{
			//�ҋ@�X�e�[�g�ɑJ�ڂ���B
			m_EnemyState = enEnemyState_Idle;
			return;
		}
		//�v���C���[��������Ȃ��Ȃ�
		else
		{
			//�ҋ@�X�e�[�g�ɑJ�ڂ���B
			m_EnemyState = enEnemyState_Idle;
		}
	}
	void Enemy_Green::ProcessIdleStateTransition()
	{
		//�����v���C���[�������Ă����Ȃ�
		if (SearchPlayer() == true)
		{
			//�U���X�e�[�g�ɑJ�ڂ���B
			m_EnemyState = enEnemyState_Attack;
		}
		else
		{
			//���ʃX�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessCommonStateTransition();
		}
	}
	void Enemy_Green::ProcessAttackStateTransition()
	{
		//�A�j���[�V�����̍Đ����I��������
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//���ʃX�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessCommonStateTransition();
		}
	}
	void Enemy_Green::ProcessDownStateTransition()
	{
		//�����蔻����폜����B
		m_charaCon.RemoveRigidBoby();
		//�A�j���[�V�����̍Đ����I��������
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//���g���폜����B
			DeleteGO(this);
		}
		return;
	}
	void Enemy_Green::ManageState()
	{
		switch (m_EnemyState)
		{
			//�ҋ@�X�e�[�g�̎��B
		case enEnemyState_Idle:
			//�ҋ@�X�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessIdleStateTransition();
			break;
			//�U���X�e�[�g�̎��B
		case enEnemyState_Attack:
			//�U���X�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessAttackStateTransition();
			break;
			//���S�X�e�[�g�̎��B
		case enEnemyState_Down:
			//���S�X�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessDownStateTransition();
			break;
		}
	}
	void Enemy_Green::PlayAnimation()
	{
		switch (m_EnemyState)
		{
			//�ҋ@�X�e�[�g�̎��B
		case enEnemyState_Idle:
			//�A�j���[�V�����̍Đ����x�B
			m_modelRender.SetAnimationSpeed(1.2f);
			//�ҋ@�A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//�U���X�e�[�g�̎��B
		case enEnemyState_Attack:
			//�A�j���[�V�����̍Đ����x�B
			m_modelRender.SetAnimationSpeed(0.3f);
			//�U���A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Attack, 1.0f);
			break;
			//���S�X�e�[�g�̎��B
		case enEnemyState_Down:
			//�A�j���[�V�����̍Đ����x�B
			m_modelRender.SetAnimationSpeed(1.1f);
			//���S�A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Down, 1.0f);
			break;
		default:
			break;
		}
	}
	void Enemy_Green::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
	{
		//�L�[�̖��O���uAttack�v�̎��B
		if (wcscmp(eventName, L"Attack") == 0)
		{
			//�C�e���쐬����B
			MakeAttack();
		}
	}
	void Enemy_Green::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}