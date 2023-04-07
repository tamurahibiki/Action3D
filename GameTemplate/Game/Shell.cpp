#include "stdafx.h"
#include "Shell.h"
#include "CollisionObject.h"
#include "Player.h"
#include "SoundList.h"

namespace
{
	const float FIRSTMULTIPLICATION = 60.0f;//最初に乗算する速度
	const float SECONDMULTIPLICATION = 1200.0f;//次に乗算する速度
	const float ROTADDITIONY = 360.0f;//モデルを回転する加算速度。
	const float SCALEMULTIPLICATION = 5.5; //乗算する大きさ
	const float COLLISONSCALEMULTIPLICATION = 60.0f; //コリジョンに乗算する大きさ
	const float DISAPPEARTIMEMAX = 1.5f;    //砲弾が消えるまでの時間
}

Shell::Shell(){}
Shell::~Shell()
{
	//コリジョンオブジェクトを削除する。
	DeleteGO(m_collisionObject);
}
bool Shell::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/sphere.tkm",false);
	//座標を設定する。
	m_modelRender.SetPosition(m_position);
	//大きさを設定する。
	m_modelRender.SetScale(Vector3::One * SCALEMULTIPLICATION);
	

	//Z方向に移動方向を設定する。
	m_moveSpeed = Vector3::AxisZ;
	//Z方向に回転。
	m_rotation.Apply(m_moveSpeed);
	//座標の移動。
	m_position += m_moveSpeed * FIRSTMULTIPLICATION;
	m_moveSpeed *= SECONDMULTIPLICATION;
	//Y軸方向に回転を加算。
	m_rotation.AddRotationDegY(ROTADDITIONY);
	
	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//球状のコリジョンを作成する。
	m_collisionObject->CreateSphere(
		m_position,//座標。
		Quaternion::Identity,//回転。
		COLLISONSCALEMULTIPLICATION * m_scale.z//大きさ。
	);
	//名前をDeadにする。
	m_collisionObject->SetName("Dead");
	//コリジョンオブジェクトが自動で削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);

	m_soundlist = FindGO<SoundList>("soundlist");

	return true;
}
void Shell::Update()
{
	m_player = FindGO<Player>("player");
	//当たり判定。
	Collision();
	//座標を移動させる。
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	//座標を設定する。
	m_modelRender.SetPosition(m_position);
	//タイマーを動かす。
	m_timer += g_gameTime->GetFrameDeltaTime();
	//1.5秒以上経ったら
	if (m_timer >= DISAPPEARTIMEMAX)
	{
		//削除する。
		DeleteGO(this);
	}
	//コリジョンオブジェクトに座標を設定する。
	m_collisionObject->SetPosition(m_position);
	//モデルの更新処理。
	m_modelRender.Update();
}
void Shell::Collision()
{
	//プレイヤーの足のコリジョンを所得する。
	const auto& legcollision = g_collisionObjectManager->FindCollisionObjects("Leg");
	//コリジョンの配列をfor文で回す。
	for (auto collision : legcollision)
	{
		//プレイヤーの足のコリジョンと自身のコリジョンが衝突したら
		if (collision->IsHit(m_collisionObject))
		{
			//踏み台ジャンプ出来るようにする。
			m_player->JunpCount = true;
			CollisionEstablishment();
			return;
		}
	}
	//プレイヤーのお尻のコリジョンを所得する。
	const auto& hipcollision = g_collisionObjectManager->FindCollisionObjects("Hip");
	//コリジョンの配列をfor文で回す。
	for (auto collision : hipcollision)
	{
		//プレイヤーのお尻のコリジョンと自身のコリジョンが衝突したら
		if (collision->IsHit(m_collisionObject))
		{
			CollisionEstablishment();
			return;
		}
	}
}
void Shell::CollisionEstablishment()
{
	//倒れた効果音を一度だけ再生する。
	if (DownSound == true)
	{
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(m_soundlist->ENEMYDOWNHIP);
		se->Play(false);//ループ再生をしない。
		se->SetVolume(0.2f);//ボリューム
		DownSound = false;
	}
	//自身を削除する。
	DeleteGO(this);
}
void Shell::Render(RenderContext& rc)
{
	//モデルの描画。
	m_modelRender.Draw(rc);
}