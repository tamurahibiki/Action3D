#include "stdafx.h"
#include "Shell.h"
#include "CollisionObject.h"
#include "Player.h"
#include "SoundList.h"

namespace
{
	const float FIRSTMULTIPLICATION = 60.0f;//�ŏ��ɏ�Z���鑬�x
	const float SECONDMULTIPLICATION = 1200.0f;//���ɏ�Z���鑬�x
	const float ROTADDITIONY = 360.0f;//���f������]������Z���x�B
	const float SCALEMULTIPLICATION = 5.5; //��Z����傫��
	const float COLLISONSCALEMULTIPLICATION = 60.0f; //�R���W�����ɏ�Z����傫��
	const float DISAPPEARTIMEMAX = 1.5f;    //�C�e��������܂ł̎���
}

Shell::Shell(){}
Shell::~Shell()
{
	//�R���W�����I�u�W�F�N�g���폜����B
	DeleteGO(m_collisionObject);
}
bool Shell::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/sphere.tkm",false);
	//���W��ݒ肷��B
	m_modelRender.SetPosition(m_position);
	//�傫����ݒ肷��B
	m_modelRender.SetScale(Vector3::One * SCALEMULTIPLICATION);
	

	//Z�����Ɉړ�������ݒ肷��B
	m_moveSpeed = Vector3::AxisZ;
	//Z�����ɉ�]�B
	m_rotation.Apply(m_moveSpeed);
	//���W�̈ړ��B
	m_position += m_moveSpeed * FIRSTMULTIPLICATION;
	m_moveSpeed *= SECONDMULTIPLICATION;
	//Y�������ɉ�]�����Z�B
	m_rotation.AddRotationDegY(ROTADDITIONY);
	
	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//����̃R���W�������쐬����B
	m_collisionObject->CreateSphere(
		m_position,//���W�B
		Quaternion::Identity,//��]�B
		COLLISONSCALEMULTIPLICATION * m_scale.z//�傫���B
	);
	//���O��Dead�ɂ���B
	m_collisionObject->SetName("Dead");
	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
	m_collisionObject->SetIsEnableAutoDelete(false);

	m_soundlist = FindGO<SoundList>("soundlist");

	return true;
}
void Shell::Update()
{
	m_player = FindGO<Player>("player");
	//�����蔻��B
	Collision();
	//���W���ړ�������B
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	//���W��ݒ肷��B
	m_modelRender.SetPosition(m_position);
	//�^�C�}�[�𓮂����B
	m_timer += g_gameTime->GetFrameDeltaTime();
	//1.5�b�ȏ�o������
	if (m_timer >= DISAPPEARTIMEMAX)
	{
		//�폜����B
		DeleteGO(this);
	}
	//�R���W�����I�u�W�F�N�g�ɍ��W��ݒ肷��B
	m_collisionObject->SetPosition(m_position);
	//���f���̍X�V�����B
	m_modelRender.Update();
}
void Shell::Collision()
{
	//�v���C���[�̑��̃R���W��������������B
	const auto& legcollision = g_collisionObjectManager->FindCollisionObjects("Leg");
	//�R���W�����̔z���for���ŉ񂷁B
	for (auto collision : legcollision)
	{
		//�v���C���[�̑��̃R���W�����Ǝ��g�̃R���W�������Փ˂�����
		if (collision->IsHit(m_collisionObject))
		{
			//���ݑ�W�����v�o����悤�ɂ���B
			m_player->JunpCount = true;
			CollisionEstablishment();
			return;
		}
	}
	//�v���C���[�̂��K�̃R���W��������������B
	const auto& hipcollision = g_collisionObjectManager->FindCollisionObjects("Hip");
	//�R���W�����̔z���for���ŉ񂷁B
	for (auto collision : hipcollision)
	{
		//�v���C���[�̂��K�̃R���W�����Ǝ��g�̃R���W�������Փ˂�����
		if (collision->IsHit(m_collisionObject))
		{
			CollisionEstablishment();
			return;
		}
	}
}
void Shell::CollisionEstablishment()
{
	//�|�ꂽ���ʉ�����x�����Đ�����B
	if (DownSound == true)
	{
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(m_soundlist->ENEMYDOWNHIP);
		se->Play(false);//���[�v�Đ������Ȃ��B
		se->SetVolume(0.2f);//�{�����[��
		DownSound = false;
	}
	//���g���폜����B
	DeleteGO(this);
}
void Shell::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);
}