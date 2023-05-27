#include "stdafx.h"
#include "Fort.h"
#include "Player.h"
#include "Player_Head.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SoundList.h"

namespace
{
	const float SEARCHRANGE  = 600.0f;//�T���͈�
	const float FORTVISION   = 360.0f;//����
	const float HEDADDITIONZ = 400.0f;//�v���C���[�̓����f���̉��s���ɉ��Z
	const float HEDADDITIONY = 350.0f;//�v���C���[�̓����f���̍����ɉ��Z
}
namespace App {
	Fort::Fort() {}
	Fort::~Fort() {}
	bool Fort::Start()
	{
		//�A�j���[�V������ǂݍ��ށB
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Fort_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animClips[enAnimationClip_Move].Load("Assets/animData/Fort_Move.tka");
		m_animClips[enAnimationClip_Move].SetLoopFlag(false);
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/gimmick/Fort.tkm", false, true, m_animClips, enAnimationCilp_Num);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
		m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
			OnAnimationEvent(clipName, eventName);
			});

		m_head = FindGO<Player_Head>("player_head");
		m_soundlist = FindGO<SoundList>("soundlist");
		return true;
	}
	void Fort::Update()
	{
		m_player = FindGO<Player>("player");
		//�X�e�[�g�̑J�ڏ����B
		ManageState();
		//�A�j���[�V�����̍Đ��B
		PlayAnimation();
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	const bool Fort::SearchPlayer() const
	{
		//�v���C���[�����C�Ɍ������x�N�g�����v�Z����B
		Vector3 diff = m_player->GetPosition() - m_position;
		//�v���C���[�ɂ�����x�߂�������
		if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
		{
			//��C����v���C���[�Ɍ������x�N�g���𐳋K������B
			diff.Normalize();
			/*��C�̐��ʂ̃x�N�g���ƁA��C����v���C���[�Ɍ������x�N�g����
			����(cos��)�����߂�B*/
			float cos = m_forward.Dot(diff);
			//����(cos��)����p�x(��)�����߂�B
			float angle = acosf(cos);
			//�p�x(��)��360����菬�������
			if (angle <= (Math::PI / FORTVISION) * FORTVISION)
			{
				//�v���C���[��������B
				return true;
			}
		}
		//�v���C���[��������Ȃ��B
		return false;
	}
	void Fort::ProcessCommonStateTransition()
	{
		//�����v���C���[�������Ă����Ȃ�
		if (SearchPlayer() == true)
		{
			//�v���C���[��`�悵�Ȃ��B
			m_player->PlayerNotDraw = true;
			//�v���C���[���C�܂ňړ�������B
			m_player->Fort_Idle = true;
			//�ʏ�J�������������Ȃ��B
			m_player->Default = false;
			//���s���J�������������Ȃ��B
			m_player->Forward = false;

			//���ʉ����Đ�����B
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->FORTIDLE);
			se->Play(false);
			se->SetVolume(0.1f);

			//�쓮�X�e�[�g�ɑJ�ڂ���B
			m_fortState = enFortState_Move;
			return;
		}
		else
		{
			//�ҋ@�X�e�[�g�ɑJ�ڂ���B
			m_fortState = enFortState_Idle;
		}
	}
	void Fort::ProcessMoveStateTransition()
	{
		//�A�j���[�V�����̍Đ����I��������
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//���ʃX�e�[�g��J�ڂ���B
			ProcessCommonStateTransition();
		}
	}
	void Fort::ManageState()
	{
		//switch���B
		switch (m_fortState)
		{
			//�ҋ@�X�e�[�g�̎��B
		case enFortState_Idle:
			//���ʃX�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessCommonStateTransition();
			break;
			//�쓮�X�e�[�g�̎��B
		case enFortState_Move:
			//�쓮�X�e�[�g�̃X�e�[�g�J�ڏ����B
			ProcessMoveStateTransition();
			break;
		}
	}
	void Fort::PlayAnimation()
	{
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.0f);
		//switch���B
		switch (m_fortState) {
			//�ҋ@�X�e�[�g�̎��B
		case enFortState_Idle:
			//�ҋ@�A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//�쓮�X�e�[�g�̎��B
		case enFortState_Move:
			//�쓮�A�j���[�V�������Đ��B
			m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
			break;
		default:
			break;
		}
	}
	void Fort::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
	{
		//�L�[�̖��O���uFort�v�̎��B
		if (wcscmp(eventName, L"Fort") == 0)
		{
			//�v���C���[���C���甭�˂���B
			m_player->Fort_Move = true;
			//�v���C���[���C�܂ňړ������邱�Ƃ��~�߂�B
			m_player->Fort_Idle = false;
			//�v���C���[�̓����f�����폜����B
			DeleteGO(m_head);
		}
		//�L�[�̖��O���uFort2�v�̎��B
		if (wcscmp(eventName, L"Fort2") == 0)
		{
			//���ʉ����Đ�����B
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->FORTSTAY);
			se->Play(false);
			se->SetVolume(0.3f);
			//�v���C���[��`�悷��B
			m_player->PlayerNotDraw = false;
		}
		//�L�[�̖��O���uFort_Hed�v�̎��B
		if (wcscmp(eventName, L"Fort_Hed") == 0)
		{
			//�v���C���[�̓����f�����쐬����B
			MakeHead();
		}
	}
	void Fort::MakeHead()
	{
		//�v���C���[�̓����f���𐶐�����B
		m_head = NewGO<Player_Head>(0, "player_head");
		//���W��ݒ肷��B
		Vector3 player_hedPosition = m_position;
		player_hedPosition.z += HEDADDITIONZ;
		player_hedPosition.y += HEDADDITIONY;
		//���W��ݒ肷��B
		m_head->SetPosition(player_hedPosition);
	}
	void Fort::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}