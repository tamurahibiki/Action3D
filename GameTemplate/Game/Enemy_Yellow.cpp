#include "stdafx.h"
#include "Enemy_Yellow.h"
#include "Player.h"
#include "CollisionObject.h"
#include "EffectList.h"
#include "SoundList.h"

namespace
{
	const float   ZERO = 0.0f;                                //�[��
	const float   SEARCHRANGE = 1500.0f;                      //�T���͈�
	const float   YELLOWVISION = 360.0f;                      //����
	const float   CHARACON = 70.0f;                           //�����蔻��̔��a�ƍ���
	const float   CHASESUBTRACTIONY = 200.0f;                 //�Ǐ]�����Z���鍂��
	const float   MOVEMULTIPLICATION = 750.0f;                //�Ǐ]�ړ����A��Z���鑬�x
	const float   INERTIAMULTIPLICATION = 0.99f;              //�����ړ����A��Z���鑬�x
	const float   SEARCHMULTIPLICATION = 0.01f;               //�������A��Z���鑬�x
	const Vector3 COLLISIONSCALE  = { 200.0f, 80.0f,200.0f }; //�R���W�����̑傫��
	const Vector3 DOWNEFFECTSCALE = { 100.0f,100.0f,100.0f }; //���S�G�t�F�N�g�̑傫��
}
namespace App {
	Enemy_Yellow::Enemy_Yellow() {}
	Enemy_Yellow::~Enemy_Yellow()
	{
		//�R���W�������폜����B
		DeleteGO(m_collisionObject);
	}
	bool Enemy_Yellow::Start()
	{
		//�A�j���[�V������ǂݍ��ށB
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Enemy_Yellow_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animClips[enAnimationClip_Discovery].Load("Assets/animData/Enemy_Yellow_Discovery.tka");
		m_animClips[enAnimationClip_Discovery].SetLoopFlag(false);
		m_animClips[enAnimationClip_Move].Load("Assets/animData/Enemy_Yellow_Move.tka");
		m_animClips[enAnimationClip_Move].SetLoopFlag(true);
		m_animClips[enAnimationClip_Down].Load("Assets/animData/Enemy_Yellow_Down.tka");
		m_animClips[enAnimationClip_Down].SetLoopFlag(false);
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/enemy/Enemy_Yellow.tkm", false, false, m_animClips, enAnimationCilp_Num);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		//�����蔻����쐬����B
		m_charaCon.Init(
			CHARACON,//���a
			CHARACON,//����
			m_position//���W
		);
		//�R���W�����I�u�W�F�N�g���쐬����B
		m_collisionObject = NewGO<CollisionObject>(0);
		Vector3 attackPosition = m_position;
		//�{�b�N�X��̃R���W�������쐬����B
		m_collisionObject->CreateBox(
			attackPosition,//���W
			Quaternion::Identity,//��]	
			COLLISIONSCALE//�傫��
		);
		//���O��Dead�ɂ���B
		m_collisionObject->SetName("Dead");
		//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
		m_collisionObject->SetIsEnableAutoDelete(false);
		//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
		m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
			OnAnimationEvent(clipName, eventName);
			});
		m_effectlist = FindGO<EffectList>("effectlist");
		m_soundlist = FindGO<SoundList>("soundlist");
		return true;
	}
	void Enemy_Yellow::Update()
	{
		m_player = FindGO<Player>("player");
		//�Ǐ]�����B
		Chase();
		//��]�����B
		Rotation();
		//�����蔻��B
		Collision();
		//�X�e�[�g�̑J�ڏ����B
		ManageState();
		//�A�j���[�V�����̍Đ��B
		PlayAnimation();
		//�R���W�����I�u�W�F�N�g�ɍ��W��ݒ肷��B
		m_collisionObject->SetPosition(m_position);
		//���f�����X�V����B
		m_modelRender.Update();
	}
	void Enemy_Yellow::Rotation()
	{
		EnemyRotation();
	}
	void Enemy_Yellow::Chase()
	{
		//�ǐՃX�e�[�g�łȂ��Ȃ�A�ǐՏ����͂��Ȃ��B
		if (m_EnemyState != enEnemyState_Move)
		{
			return;
		}
		//���W��ݒ肷��B
		m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
		Vector3 modelPosition = m_position;
		m_modelRender.SetPosition(modelPosition);
	}
	void Enemy_Yellow::Collision()
	{
		//�v���C���[�̑��̃R���W��������������B
		const auto& legcollision = g_collisionObjectManager->FindCollisionObjects("Leg");
		//�R���W�����̔z���for���ŉ񂷁B
		for (auto collision : legcollision)
		{
			//�v���C���[�̑��̃R���W�����Ǝ��g�̓����蔻�肪�Փ˂�����
			if (collision->IsHit(m_charaCon))
			{
				//�����蔻����폜����B
				DeleteGO(m_collisionObject);
				//�|�����ʉ�����x�����Đ�����B
				if (DownSound == true)
				{
					//���ݑ�W�����v���o����悤�ɂ���B
					m_player->JunpCount = true;
					//�G�t�F�N�g��ݒ肷��B
					m_effectEmitter = NewGO <EffectEmitter>(0);
					m_effectEmitter->Init(m_effectlist->ENEMYDAMAGE);
					//���W��ݒ肷��B
					Vector3 effectPosition = m_position;
					m_effectEmitter->SetPosition(effectPosition);
					//��]��ݒ肷��B
					m_effectEmitter->SetRotation(m_rotation);
					//�傫����ݒ肷��B
					m_effectEmitter->SetScale(DOWNEFFECTSCALE);
					//�G�t�F�N�g���Đ�����B
					m_effectEmitter->Play();
					//�v���C���[�̘A�����݂��������Z����B
					m_player->Enemy_JunpCount++;

					//���ʉ���ݒ肷��B
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(m_soundlist->ENEMYDOWN);
					//���[�v�Đ����Ȃ��B
					se->Play(false);
					//�{�����[���̐ݒ�B
					se->SetVolume(0.2f);
					DownSound = false;
				}
				//�_�E���X�e�[�g�ɑJ�ڂ���B
				m_EnemyState = enEnemyState_Down;
				return;
			}
		}
		//�v���C���[�̂��K�̃R���W��������������B
		const auto& hipcollision = g_collisionObjectManager->FindCollisionObjects("Hip");
		//�R���W�����̔z���for���ŉ񂷁B
		for (auto collision : hipcollision)
		{
			//�v���C���[�̑��̃R���W�����Ǝ��g�̓����蔻�肪�Փ˂�����
			if (collision->IsHit(m_charaCon))
			{
				//�����蔻����폜����B
				DeleteGO(m_collisionObject);
				//�|�����ʉ�����x�����Đ�����B
				if (DownSound == true)
				{
					//���ʉ���ݒ肷��B
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(m_soundlist->ENEMYDOWNHIP);
					//���[�v�Đ����Ȃ��B
					se->Play(false);
					//�{�����[���̐ݒ�B
					se->SetVolume(0.2f);
					DownSound = false;
				}
				//�_�E���X�e�[�g�ɑJ�ڂ���B
				m_EnemyState = enEnemyState_Down;
				return;
			}
		}
	}
	const bool Enemy_Yellow::SearchPlayer() const
	{
		//�v���C���[�����S���Ă��炸�A�S�[�����Ă��Ȃ����
		if (m_player->Dead == false && m_player->Goal == false)
		{
			//�v���C���[������ł���G�l�~�[�Ɍ������x�N�g�����v�Z����B
			Vector3 diff = m_player->GetPosition() - m_position;
			//�v���C���[�ɂ�����x�߂�������
			if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
			{
				//���ł���G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K������B
				diff.Normalize();
				/*���ł���G�l�~�[�̐��ʂ̃x�N�g���ƁA
				���ł���G�l�~�[����v���C���[�Ɍ������x�N�g����
				����(cos��)�����߂�B*/
				float cos = m_forward.Dot(diff);
				//����(cos��)����p�x(��)�����߂�B
				float angle = acosf(cos);
				//�p�x(��)��360����菬�������
				if (angle <= (Math::PI / YELLOWVISION) * YELLOWVISION)
				{
					//�v���C���[��������B
					return true;
				}
			}
			//�v���C���[��������Ȃ��B
			return false;
		}
	}
	void Enemy_Yellow::ProcessCommonStateTransition()
	{
		//�v���C���[������ł���G�l�~�[�Ɍ������x�N�g�����v�Z����B
		Vector3 diff = m_player->GetPosition() - m_position;
		//�v���C���[�̏��������v�Z����B
		diff.y -= CHASESUBTRACTIONY;
		//�����v���C���[�������Ă����Ȃ�
		if (SearchPlayer() == true)
		{
			//�ǂ������Ĉړ��ł���Ȃ�
			if (Move == true) {
				//�ǂ������Ă���G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K������B
				diff.Normalize();
				//�ړ����x��ݒ肷��B
				m_moveSpeed = diff * MOVEMULTIPLICATION;
				//�������x�Ɍ��݂̈ړ����x��n���Ă����B
				m_inertiaSpeed = m_moveSpeed;
			}
			else {
				//�����X�e�[�g�ɑJ�ڂ���B
				m_EnemyState = enEnemyState_Discovery;
				//�ړ����x��ݒ肷��B
				m_moveSpeed = diff * SEARCHMULTIPLICATION;
				//�������ς��Ȃ��悤�ɂ���B
				m_moveSpeed.y = ZERO;
			}
			return;
		}
		//�v���C���[��������Ȃ��Ȃ�
		else
		{
			//�������x��0.99����Z���Ă���
			m_inertiaSpeed *= INERTIAMULTIPLICATION;
			//���݂̈ړ����x�Ɋ������x��n���Ă����B
			m_moveSpeed = m_inertiaSpeed;
			//�ǂ������Ĉړ��ł��Ȃ�����B
			Move = false;
			//�ҋ@�X�e�[�g�ɑJ�ڂ���B
			m_EnemyState = enEnemyState_Idle;
		}
	}
	void Enemy_Yellow::ProcessDiscoveryStateTransition()
	{
		//�A�j���[�V�����̍Đ����I��������
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//�ǂ������Ĉړ��ł���悤�ɂ���B
			Move = true;
			//�ړ��X�e�[�g�ɑJ�ڂ���B
			m_EnemyState = enEnemyState_Move;
		}
	}
	void Enemy_Yellow::ProcessDownStateTransition()
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
	void Enemy_Yellow::ManageState()
	{
		switch (m_EnemyState)
		{
			//�ҋ@�X�e�[�g�̎��B
		case enEnemyState_Idle:
			//���ʂ̃X�e�[�g�J�ڏ����B
			ProcessCommonStateTransition();
			break;
			//�����X�e�[�g�̎��B
		case enEnemyState_Discovery:
			//�����X�e�[�g�̑J�ڏ����B
			ProcessDiscoveryStateTransition();
			break;
			//�ړ��X�e�[�g�̎��B
		case enEnemyState_Move:
			//���ʂ̃X�e�[�g�J�ڏ����B
			ProcessCommonStateTransition();
			break;
			//���S�X�e�[�g�̎��B
		case enEnemyState_Down:
			//���S�X�e�[�g�̑J�ڏ����B
			ProcessDownStateTransition();
			break;
		}
	}
	void Enemy_Yellow::PlayAnimation()
	{
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.2f);
		switch (m_EnemyState)
		{
			//�ҋ@�X�e�[�g�̎��B
		case enEnemyState_Idle:
			//�ҋ@�A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//�����X�e�[�g�̎��B
		case enEnemyState_Discovery:
			//�A�j���[�V�����̍Đ����x�B
			m_modelRender.SetAnimationSpeed(1.0f);
			//�����A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Discovery, 1.0f);
			break;
			//�ړ��X�e�[�g�̎��B
		case enEnemyState_Move:
			//�ړ��A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
			break;
			//���S�X�e�[�g�̎��B
		case enEnemyState_Down:
			//�A�j���[�V�����̍Đ����x�B
			m_modelRender.SetAnimationSpeed(1.5f);
			//���S�A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Down, 1.0f);
			break;
		default:
			break;
		}
	}
	void Enemy_Yellow::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
	{
		//�L�[�̖��O���uMove_Sound�v�̎��B
		if (wcscmp(eventName, L"Move_Sound") == 0)
		{
			//�ǂ������Ĉړ����Ă���Ȃ�
			if (Move == true) {
				//���ʉ��̐ݒ�B
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(m_soundlist->ENEMYMOVE2);
				//���[�v�Đ����Ȃ��B
				se->Play(false);
				//�{�����[���̐ݒ�B
				se->SetVolume(0.15f);
			}
		}
	}
	void Enemy_Yellow::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}