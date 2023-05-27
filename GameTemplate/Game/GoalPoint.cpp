#include "stdafx.h"
#include "GoalPoint.h"
#include "CollisionObject.h"
#include "Game.h"
#include "Player.h"
namespace
{
	const float SEARCHRANGE = 600.0f;     //�T���͈�
	const float GOALPOINTVISION = 360.0f; //����
}
namespace App {
	GoalPoint::GoalPoint() {}
	GoalPoint::~GoalPoint() {}
	bool GoalPoint::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/gimmick/GoalPoint.tkm", false, false);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		m_game = FindGO<Game>("game");

		return true;
	}
	void GoalPoint::Update()
	{
		m_player = FindGO<Player>("player");
		//�����v���C���[�������Ă����Ȃ�
		if (SearchPlayer() == true)
		{
			//�v���C���[���S�[����Ԃɂ���B
			m_player->Goal = true;
			//�ʏ�J�������������Ȃ��B
			m_player->Default = false;
			//���Ԓn�_���B�̏������폜����B
			m_game->Try = false;
			return;
		}
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	const bool GoalPoint::SearchPlayer() const
	{
		//�v���C���[����S�[���|�C���g�Ɍ������x�N�g�����v�Z����B
		Vector3 diff = m_player->GetPosition() - m_position;
		//�v���C���[��������x�߂�������
		if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
		{
			//�S�[���|�C���g����v���C���[�Ɍ������x�N�g���𐳋K������B
			diff.Normalize();
			/*�S�[���|�C���g�̐��ʂ̃x�N�g���ƁA
			�S�[���|�C���g����v���C���[�Ɍ������x�N�g����
			����(cos��)�����߂�B*/
			float cos = m_forward.Dot(diff);
			//����(cos��)����p�x(��)�����߂�B
			float angle = acosf(cos);
			//�p�x(��)��360����菬�������
			if (angle <= (Math::PI / GOALPOINTVISION) * GOALPOINTVISION)
			{
				//�v���C���[��������B
				return true;
			}
		}
		//�v���C���[��������Ȃ��B
		return false;
	}
	void GoalPoint::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}