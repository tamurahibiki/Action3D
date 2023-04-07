#include "stdafx.h"
#include "FortTop.h"
#include "Player.h"
namespace
{
	const float SEARCHRANGE = 800.0f;//�T���͈�
}
FortTop::FortTop() {}
FortTop::~FortTop() {}

bool FortTop::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Box.tkm", true);
	//���W�A��]�A�傫����ݒ肷��B
	SetupTRS();
	return true;
}
void FortTop::Update()
{
	m_player = FindGO<Player>("player");
	//���f���̍X�V�B
	m_modelRender.Update();
	//�v���C���[�����C�ړ��̒��_�|�C���g�|�C���g�Ɍ������x�N�g�����v�Z����B
	Vector3 diff = m_player->GetPosition() - m_position;
	//�v���C���[�ɂ�����x�߂�������
	if (diff.Length() <= SEARCHRANGE)
	{
		//��C�ړ����㏸�J�������������Ȃ��B
		m_player->Fort_Move = false;
		//��C�ړ������~�J�����ɕύX����B
		m_player->Fort_Top = true;
	}
}