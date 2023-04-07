#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "GoalPoint.h"
#include "Game.h"

namespace
{
	const float DEFAULTTARGETY = 600.0f;        //�^�[�Q�b�g��600.0f�������B
	const float GOALTARGETY = 400.0f;           //�^�[�Q�b�g��400.0f�������B
	const float GOALPOSMULTIPLICATION = 1500.0f;//�^�[�Q�b�g����1500.0f�����B

	//////////////////////////////////////
	//��������g�p���Ă���֐��̑啶��������Ė��̂�t����B
	//////////////////////////////////////
	//Default,ForWard�̒����_���王�_�܂ł̃x�N�g���B
	const Vector3 DFWPOS = { 2000.0f, 500.0f, 0.0f };
	//FortStay�̒����_���王�_�܂ł̃x�N�g���B
	const Vector3 FSPOS = { 2000.0f, 1000.0f, 0.0f };
	//FortMoveFall�̒����_���王�_�܂ł̃x�N�g���B
	const Vector3 FMFPOS = { 1750.0f, 1000.0f, 0.0f };
	//FortMoveUp,Goal�̒����_���王�_�܂ł̃x�N�g���B
	const Vector3 FMUGPOS = { 1100.0f, 1000.0f, 0.0f };
	//Dead�̒����_���王�_�܂ł̃x�N�g���B
	const Vector3 DPOS = { 10.0f, 1500.0f, 0.0f };
	//Default.FortStay,FortMoveUp,FortMoveFall�̉�]�p�x�B
	const float DFSFMUFMFROT = 90.0f;
	//ForWard�̉�]�p�x�B
	const float FWROT = 45.0f;
	//////////////////////////////////////
	//�g�p���Ă���֐��̑啶��������Ė��̂�t����̂͂����܂ŁB
	//////////////////////////////////////
}
GameCamera::GameCamera(){}
GameCamera::~GameCamera(){}
bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");
	m_goal = FindGO<GoalPoint>("goalpoint");
	m_game = FindGO<Game>("game");
	return true;
}
void GameCamera::DefaultUpdatePositionAndTarget()
{
	//�J�������X�V�B
	//�����_���v�Z����B
	Vector3 target= m_player->GetPosition();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += DEFAULTTARGETY;
	//���_���v�Z����B
	Vector3 pos;
	pos = target + m_toCameraPos;
	//�J�����̏����B	
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
}
void GameCamera::GoalUpdatePositionAndTarget()
{
	//�J�������X�V�B
	//�����_���v�Z����.
	Vector3 target = m_player->GetPosition();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += GOALTARGETY;
	//�v���C���[�ƃS�[���|�C���g�̃x�N�g�������Z����B
	Vector3 V = m_player->GetPosition()-m_goal->GetPosition();
	//Y���͍l�����Ȃ��B
	V.y = 0;
	//���K������B
	V.Normalize();
	//���_���v�Z����B
	Vector3 pos = target + V * GOALPOSMULTIPLICATION;
	//�v���C���[���W�����v���Ă��Ȃ����
	if (m_player->PlayerJunp == false)
	{
		//�J�����̏����B
		g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);
	}
}
void GameCamera::Update()
{
	//�v���C���[�����S���Ă���Ȃ�
	if (m_player->Dead==true)
	{
		//���S���̃J�����A���O���ɕύX����B
		DeadCamera();	
		//���_�ƒ����_���X�V����B
		DefaultUpdatePositionAndTarget();
	}

	//�v���C���[�������Ă���
	else
	{
		//�v���C���[����C�Ɉړ����Ă���Ȃ�
		if (m_player->Fort_Idle == true &&
			m_player->Fort_Move == false)
		{
			//��C���ˑO�̃J�����A���O���ɕύX����B
			FortStayCamera();
			//���_�ƒ����_���X�V����B
			DefaultUpdatePositionAndTarget();
		}
		//�v���C���[����C���甭�˂���Ă���Ȃ�
		if (m_player->Fort_Idle == false &&
			m_player->Fort_Move == true)
		{
			//��C�ړ����㏸�̃J�����A���O���ɕύX����B
			FortMoveUpCamera();
			//���_�ƒ����_���X�V����B
			DefaultUpdatePositionAndTarget();
		}
		//�v���C���[����C�ړ��̒��_�|�C���g�ɂ���Ȃ�
		if (m_player->Fort_Top == true)
		{
			//��C�ړ������~�̃J�����A���O���ɕύX����B
			FortMoveFallCamera();
			//���_�ƒ����_���X�V����B
			DefaultUpdatePositionAndTarget();
		}
		//�v���C���[���S�[�����Ă���Ȃ�
		if (m_player->Goal == true)
		{
			//�S�[�����̃J�����A���O���ɕύX����B
			GoalCamera();
			//�S�[�����̎��_�ƒ����_���X�V����B
			GoalUpdatePositionAndTarget();
		}
		//�v���C���[�����s���J�����ɕύX����|�C���g�ɂ���Ȃ�
		if (m_player->Forward == true)
		{
			//���s����������J�����A���O���ɕύX����B
			ForWardCamera();
			//���_�ƒ����_���X�V����B
			DefaultUpdatePositionAndTarget();
		}
		//�v���C���[���ʏ�J�����ɕύX����|�C���g�ɂ���Ȃ�
		if (m_player->Default == true)
		{
			//�ʏ�̃J�����A���O���ɕύX����B
			DefaultCamera();
			//���_�ƒ����_���X�V����B
			DefaultUpdatePositionAndTarget();
		}
	}
}
void GameCamera::DefaultCamera()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(DFWPOS);
	//���Ԓn�_�ɓ��B���Ă�����
	if (m_game->Try == true)
	{
	  //�J������90����]������B
      Quaternion qRot;
	  qRot.SetRotationDeg(Vector3::AxisY, DFSFMUFMFROT);
	  qRot.Apply(m_toCameraPos);
	}
}
void GameCamera::ForWardCamera()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(DFWPOS);
	//�J������45����]������B
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, FWROT);
	qRot.Apply(m_toCameraPos);
}
void GameCamera::FortStayCamera()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(FSPOS);
	//�J������-90����]������B
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, -DFSFMUFMFROT);
	qRot.Apply(m_toCameraPos);
}
void GameCamera::FortMoveUpCamera()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(FMUGPOS);
	//�J������90����]������B
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, DFSFMUFMFROT);
	qRot.Apply(m_toCameraPos);
}
void GameCamera::FortMoveFallCamera()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(FMFPOS);
	//�J������90����]������B
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, DFSFMUFMFROT);
	qRot.Apply(m_toCameraPos);
}
void GameCamera::GoalCamera()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(FMUGPOS);
}
void GameCamera::DeadCamera()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(DPOS);
}