#include "stdafx.h"
#include "GroundMove.h"
#include "CollisionObject.h"

namespace
{
	//コリジョンのサイズ。
	const Vector3 COLLISIONSIZE={ 1950.0f,6000.0f,3950.0f };
	//コリジョンを100.0上げる。
	const float COLLISIONHEDADDITIONY = 100.0f;
	//モデルを回転する加算速度。
	const float ADDROTATION = 2.0f;
}
namespace App {
	GroundMove::GroundMove() {}
	GroundMove::~GroundMove()
	{
		//コリジョンを削除する。
		DeleteGO(m_collisionObject);
	}
	bool GroundMove::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/gimmick/GroundMove.tkm", true, false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		//当たり判定を作成する。
		m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
			m_modelRender.GetModel().GetWorldMatrix());

		//コリジョンオブジェクトを作成する。
		m_collisionObject = NewGO<CollisionObject>(0);
		//コリジョンの座標を設定する。
		Vector3 m_collisionposition = m_position;
		m_collisionposition.y + COLLISIONHEDADDITIONY;
		//ボックス状のコリジョンを作成する。
		m_collisionObject->CreateBox(m_collisionposition, Quaternion::Identity, COLLISIONSIZE);
		//名前をMoveにする。
		m_collisionObject->SetName("Move");
		//コリジョンオブジェクトが自動で削除されないようにする。
		m_collisionObject->SetIsEnableAutoDelete(false);

		return true;
	}
	void GroundMove::Update()
	{
		//常にモデルがX軸方向に回転するようにする。
		m_rotation.AddRotationDegX(ADDROTATION);
		//回転を設定する。
		m_modelRender.SetRotation(m_rotation);
		//モデルの更新。
		m_modelRender.Update();
	}
	void GroundMove::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}