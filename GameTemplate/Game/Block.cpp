#include "stdafx.h"
#include "block.h"
#include "Player.h"
#include "CollisionObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "EffectList.h"
#include "SoundList.h"

namespace
{
	const float COLLISIONADDITIONY = 100.0f;                   //�R���W�����̍��W��100�グ��B
	const Vector3 COLLISIONSCALE   = { 150.0f, 50.0f, 150.0f };//�R���W�����̑傫��
	const Vector3 EFFECTSCALE      = { 100.0f,100.0f,100.0f }; //�G�t�F�N�g�̑傫��
}
namespace App {
	Block::Block() {}
	Block::~Block()
	{
		//�R���W�������폜����B
		DeleteGO(m_collisionObject);
	}
	bool Block::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/gimmick/block.tkm", false, false);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		//�R���W�����I�u�W�F�N�g���쐬����B
		m_collisionObject = NewGO<CollisionObject>(0);
		//�R���W�����̍��W��ݒ肷��B
		Vector3 CollisionPosition = m_position;
		CollisionPosition.y += COLLISIONADDITIONY;
		//�{�b�N�X��̃R���W�������쐬����B
		m_collisionObject->CreateBox(
			CollisionPosition,//���W
			Quaternion::Identity,//��]
			COLLISIONSCALE//�傫��
		);
		//���O��Block�ɂ���B
		m_collisionObject->SetName("Block");
		//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
		m_collisionObject->SetIsEnableAutoDelete(false);

		m_effectlist = FindGO<EffectList>("effectlist");
		m_soundlist = FindGO<SoundList>("soundlist");
		m_player = FindGO<Player>("player");

		return true;
	}
	void Block::Update()
	{
		//�����蔻��B
		Collision();
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Block::Collision()
	{
		//�v���C���[�̓��̃R���W��������������B
		const auto& hedcollision = g_collisionObjectManager->FindCollisionObjects("Head");
		//�R���W�����̔z���for���ŉ񂷁B
		for (auto collision : hedcollision)
		{
			//�v���C���[�̓��̃R���W�����Ǝ��g�̃R���W�������Փ˂�����
			if (collision->IsHit(m_collisionObject))
			{
				//�v���C���[�ɓ��ƃu���b�N���Փ˂������Ƃ�ʒm����B
				m_player->Block_Hed = true;
				CollisionEstablishment();
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
			}
		}
	}
	void Block::CollisionEstablishment()
	{
		//////////////////////////////////////
		//��������G�t�F�N�g�Ɋւ���R�[�h���L�q����B
		//////////////////////////////////////
		//�G�t�F�N�g��ݒ肷��B
		m_effectEmitter = NewGO <EffectEmitter>(0);
		m_effectEmitter->Init(m_effectlist->BLOCK);
		//���W��ݒ肷��B
		Vector3 effectPosition = m_position;
		m_effectEmitter->SetPosition(effectPosition);
		//��]��ݒ肷��B
		m_effectEmitter->SetRotation(m_rotation);
		//�傫����ݒ肷��B
		m_effectEmitter->SetScale(EFFECTSCALE);
		//�G�t�F�N�g���Đ�����B
		m_effectEmitter->Play();
		//////////////////////////////////////
		//�G�t�F�N�g�Ɋւ���R�[�h���L�q�͂����܂ŁB
		//////////////////////////////////////

		//////////////////////////////////////
		//����������ʉ��Ɋւ���R�[�h���L�q����B
		//////////////////////////////////////
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(m_soundlist->BLOCK);
		//���[�v���Ȃ��B
		se->Play(false);
		//�{�����[����ݒ肷��B
		se->SetVolume(0.6f);
		//////////////////////////////////////
		//�G�t�F�N�g�Ɋւ���R�[�h���L�q�͂����܂ŁB
		//////////////////////////////////////
		//���g���폜����B
		DeleteGO(this);
	}
	void Block::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}