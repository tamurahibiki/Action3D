#include "stdafx.h"
#include "Default.h"
#include "Player.h"
namespace
{
	const float SEARCHRANGE = 800.0f;//�T���͈�
}

Default::Default() {}
Default::~Default() {}
bool Default::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Box.tkm", true);
	//���W�A��]�A�傫����ݒ肷��B
	SetupTRS();
	
	return true;
}
void Default::Update()
{
	m_player = FindGO<Player>("player");
	//���f���̍X�V�B
	m_modelRender.Update();

	//�v���C���[����ʏ�J�����ɕύX����|�C���g�Ɍ������x�N�g�����v�Z����B
	Vector3 diff = m_player->GetPosition() - m_position;
	//�v���C���[�ɂ�����x�߂�������
	if (diff.Length() <= SEARCHRANGE)
	{
		//�v���C���[�̈ړ��������ێ�����B
		if (m_player->Default == false) {
			m_player->EnableUsingLastFrameMoveDirection();
		}
		//�ʏ�J�����ɕύX����B
		m_player->Default = true;
		//���s���J�������������Ȃ��B
		m_player->Forward = false;
	}
}