#include "stdafx.h"
#include "GroundMove.h"
#include "CollisionObject.h"

namespace
{
	//�R���W�����̃T�C�Y�B
	const Vector3 COLLISIONSIZE={ 1950.0f,6000.0f,3950.0f };
	//�R���W������100.0�グ��B
	const float COLLISIONHEDADDITIONY = 100.0f;
	//���f������]������Z���x�B
	const float ADDROTATION = 2.0f;
}
namespace App {
	GroundMove::GroundMove() {}
	GroundMove::~GroundMove()
	{
		//�R���W�������폜����B
		DeleteGO(m_collisionObject);
	}
	bool GroundMove::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/gimmick/GroundMove.tkm", true, false);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		//�����蔻����쐬����B
		m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
			m_modelRender.GetModel().GetWorldMatrix());

		//�R���W�����I�u�W�F�N�g���쐬����B
		m_collisionObject = NewGO<CollisionObject>(0);
		//�R���W�����̍��W��ݒ肷��B
		Vector3 m_collisionposition = m_position;
		m_collisionposition.y + COLLISIONHEDADDITIONY;
		//�{�b�N�X��̃R���W�������쐬����B
		m_collisionObject->CreateBox(m_collisionposition, Quaternion::Identity, COLLISIONSIZE);
		//���O��Move�ɂ���B
		m_collisionObject->SetName("Move");
		//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
		m_collisionObject->SetIsEnableAutoDelete(false);

		return true;
	}
	void GroundMove::Update()
	{
		//��Ƀ��f����X�������ɉ�]����悤�ɂ���B
		m_rotation.AddRotationDegX(ADDROTATION);
		//��]��ݒ肷��B
		m_modelRender.SetRotation(m_rotation);
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void GroundMove::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}