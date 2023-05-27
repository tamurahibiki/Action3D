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
	const float COLLISIONADDITIONY = 100.0f;                   //コリジョンの座標を100上げる。
	const Vector3 COLLISIONSCALE   = { 150.0f, 50.0f, 150.0f };//コリジョンの大きさ
	const Vector3 EFFECTSCALE      = { 100.0f,100.0f,100.0f }; //エフェクトの大きさ
}
namespace App {
	Block::Block() {}
	Block::~Block()
	{
		//コリジョンを削除する。
		DeleteGO(m_collisionObject);
	}
	bool Block::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/gimmick/block.tkm", false, false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		//コリジョンオブジェクトを作成する。
		m_collisionObject = NewGO<CollisionObject>(0);
		//コリジョンの座標を設定する。
		Vector3 CollisionPosition = m_position;
		CollisionPosition.y += COLLISIONADDITIONY;
		//ボックス状のコリジョンを作成する。
		m_collisionObject->CreateBox(
			CollisionPosition,//座標
			Quaternion::Identity,//回転
			COLLISIONSCALE//大きさ
		);
		//名前をBlockにする。
		m_collisionObject->SetName("Block");
		//コリジョンオブジェクトが自動で削除されないようにする。
		m_collisionObject->SetIsEnableAutoDelete(false);

		m_effectlist = FindGO<EffectList>("effectlist");
		m_soundlist = FindGO<SoundList>("soundlist");
		m_player = FindGO<Player>("player");

		return true;
	}
	void Block::Update()
	{
		//当たり判定。
		Collision();
		//モデルの更新。
		m_modelRender.Update();
	}
	void Block::Collision()
	{
		//プレイヤーの頭のコリジョンを所得する。
		const auto& hedcollision = g_collisionObjectManager->FindCollisionObjects("Head");
		//コリジョンの配列をfor文で回す。
		for (auto collision : hedcollision)
		{
			//プレイヤーの頭のコリジョンと自身のコリジョンが衝突したら
			if (collision->IsHit(m_collisionObject))
			{
				//プレイヤーに頭とブロックが衝突したことを通知する。
				m_player->Block_Hed = true;
				CollisionEstablishment();
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
			}
		}
	}
	void Block::CollisionEstablishment()
	{
		//////////////////////////////////////
		//ここからエフェクトに関するコードを記述する。
		//////////////////////////////////////
		//エフェクトを設定する。
		m_effectEmitter = NewGO <EffectEmitter>(0);
		m_effectEmitter->Init(m_effectlist->BLOCK);
		//座標を設定する。
		Vector3 effectPosition = m_position;
		m_effectEmitter->SetPosition(effectPosition);
		//回転を設定する。
		m_effectEmitter->SetRotation(m_rotation);
		//大きさを設定する。
		m_effectEmitter->SetScale(EFFECTSCALE);
		//エフェクトを再生する。
		m_effectEmitter->Play();
		//////////////////////////////////////
		//エフェクトに関するコードを記述はここまで。
		//////////////////////////////////////

		//////////////////////////////////////
		//ここから効果音に関するコードを記述する。
		//////////////////////////////////////
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(m_soundlist->BLOCK);
		//ループしない。
		se->Play(false);
		//ボリュームを設定する。
		se->SetVolume(0.6f);
		//////////////////////////////////////
		//エフェクトに関するコードを記述はここまで。
		//////////////////////////////////////
		//自身を削除する。
		DeleteGO(this);
	}
	void Block::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}