#include "stdafx.h"
#include "Enemy_Yellow.h"
#include "InGame/Player/Player.h"
#include "CollisionObject.h"
#include "EffectList.h"
#include "SoundList.h"

namespace
{
	const float   ZERO = 0.0f;                                //ゼロ
	const float   SEARCHRANGE = 1500.0f;                      //探索範囲
	const float   YELLOWVISION = 360.0f;                      //視野
	const float   CHARACON = 70.0f;                           //当たり判定の半径と高さ
	const float   CHASESUBTRACTIONY = 200.0f;                 //追従時減算する高さ
	const float   MOVEMULTIPLICATION = 750.0f;                //追従移動時、乗算する速度
	const float   INERTIAMULTIPLICATION = 0.99f;              //慣性移動時、乗算する速度
	const float   SEARCHMULTIPLICATION = 0.01f;               //発見時、乗算する速度
	const Vector3 COLLISIONSCALE  = { 200.0f, 80.0f,200.0f }; //コリジョンの大きさ
	const Vector3 DOWNEFFECTSCALE = { 100.0f,100.0f,100.0f }; //死亡エフェクトの大きさ
}
namespace App {
	Enemy_Yellow::Enemy_Yellow() {}
	Enemy_Yellow::~Enemy_Yellow()
	{
		//コリジョンを削除する。
		DeleteGO(m_collisionObject);
	}
	bool Enemy_Yellow::Start()
	{
		//アニメーションを読み込む。
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Enemy_Yellow_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animClips[enAnimationClip_Discovery].Load("Assets/animData/Enemy_Yellow_Discovery.tka");
		m_animClips[enAnimationClip_Discovery].SetLoopFlag(false);
		m_animClips[enAnimationClip_Move].Load("Assets/animData/Enemy_Yellow_Move.tka");
		m_animClips[enAnimationClip_Move].SetLoopFlag(true);
		m_animClips[enAnimationClip_Down].Load("Assets/animData/Enemy_Yellow_Down.tka");
		m_animClips[enAnimationClip_Down].SetLoopFlag(false);
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/enemy/Enemy_Yellow.tkm", false,m_animClips, enAnimationCilp_Num);
		//座標、回転、大きさを設定する。
		SetupTRS();

		//当たり判定を作成する。
		m_charaCon.Init(
			CHARACON,//半径
			CHARACON,//高さ
			m_position//座標
		);
		//コリジョンオブジェクトを作成する。
		m_collisionObject = NewGO<CollisionObject>(0);
		Vector3 attackPosition = m_position;
		//ボックス状のコリジョンを作成する。
		m_collisionObject->CreateBox(
			attackPosition,//座標
			Quaternion::Identity,//回転	
			COLLISIONSCALE//大きさ
		);
		//名前をDeadにする。
		m_collisionObject->SetName("Dead");
		//コリジョンオブジェクトが自動で削除されないようにする。
		m_collisionObject->SetIsEnableAutoDelete(false);
		//アニメーションイベント用の関数を設定する。
		m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
			OnAnimationEvent(clipName, eventName);
			});
		m_effectlist = FindGO<EffectList>("effectlist");
		m_soundlist = FindGO<SoundList>("soundlist");
		return true;
	}
	void Enemy_Yellow::Update()
	{
		m_player = FindGO<Player>("player");
		//追従処理。
		Chase();
		//回転処理。
		Rotation();
		//当たり判定。
		Collision();
		//ステートの遷移処理。
		ManageState();
		//アニメーションの再生。
		PlayAnimation();
		//コリジョンオブジェクトに座標を設定する。
		m_collisionObject->SetPosition(m_position);
		//モデルを更新する。
		m_modelRender.Update();
	}
	void Enemy_Yellow::Rotation()
	{
		EnemyRotation();
	}
	void Enemy_Yellow::Chase()
	{
		//追跡ステートでないなら、追跡処理はしない。
		if (m_EnemyState != enEnemyState_Move)
		{
			return;
		}
		//座標を設定する。
		m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
		Vector3 modelPosition = m_position;
		m_modelRender.SetPosition(modelPosition);
	}
	void Enemy_Yellow::Collision()
	{
		//プレイヤーの足のコリジョンを所得する。
		const auto& legcollision = g_collisionObjectManager->FindCollisionObjects("Leg");
		//コリジョンの配列をfor文で回す。
		for (auto collision : legcollision)
		{
			//プレイヤーの足のコリジョンと自身の当たり判定が衝突したら
			if (collision->IsHit(m_charaCon))
			{
				//当たり判定を削除する。
				DeleteGO(m_collisionObject);
				//倒れる効果音を一度だけ再生する。
				if (DownSound == true)
				{
					//踏み台ジャンプを出来るようにする。
					m_player->JunpCount = true;
					//エフェクトを設定する。
					m_effectEmitter = NewGO <EffectEmitter>(0);
					m_effectEmitter->Init(m_effectlist->ENEMYDAMAGE);
					//座標を設定する。
					Vector3 effectPosition = m_position;
					m_effectEmitter->SetPosition(effectPosition);
					//回転を設定する。
					m_effectEmitter->SetRotation(m_rotation);
					//大きさを設定する。
					m_effectEmitter->SetScale(DOWNEFFECTSCALE);
					//エフェクトを再生する。
					m_effectEmitter->Play();
					//プレイヤーの連続踏みつけ数を加算する。
					m_player->Enemy_JunpCount++;

					//効果音を設定する。
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(m_soundlist->ENEMYDOWN);
					//ループ再生しない。
					se->Play(false);
					//ボリュームの設定。
					se->SetVolume(0.2f);
					DownSound = false;
				}
				//ダウンステートに遷移する。
				m_EnemyState = enEnemyState_Down;
				return;
			}
		}
		//プレイヤーのお尻のコリジョンを所得する。
		const auto& hipcollision = g_collisionObjectManager->FindCollisionObjects("Hip");
		//コリジョンの配列をfor文で回す。
		for (auto collision : hipcollision)
		{
			//プレイヤーの足のコリジョンと自身の当たり判定が衝突したら
			if (collision->IsHit(m_charaCon))
			{
				//当たり判定を削除する。
				DeleteGO(m_collisionObject);
				//倒れる効果音を一度だけ再生する。
				if (DownSound == true)
				{
					//効果音を設定する。
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(m_soundlist->ENEMYDOWNHIP);
					//ループ再生しない。
					se->Play(false);
					//ボリュームの設定。
					se->SetVolume(0.2f);
					DownSound = false;
				}
				//ダウンステートに遷移する。
				m_EnemyState = enEnemyState_Down;
				return;
			}
		}
	}
	const bool Enemy_Yellow::SearchPlayer() const
	{
		//プレイヤーが死亡しておらず、ゴールしていなければ
		if (m_player->Dead == false && m_player->Goal == false)
		{
			//プレイヤーから飛んでいるエネミーに向かうベクトルを計算する。
			Vector3 diff = m_player->GetPosition() - m_position;
			//プレイヤーにある程度近かったら
			if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
			{
				//飛んでいるエネミーからプレイヤーに向かうベクトルを正規化する。
				diff.Normalize();
				/*飛んでいるエネミーの正面のベクトルと、
				飛んでいるエネミーからプレイヤーに向かうベクトルの
				内積(cosθ)を求める。*/
				float cos = m_forward.Dot(diff);
				//内積(cosθ)から角度(θ)を求める。
				float angle = acosf(cos);
				//角度(θ)が360°より小さければ
				if (angle <= (Math::PI / YELLOWVISION) * YELLOWVISION)
				{
					//プレイヤーを見つける。
					return true;
				}
			}
			//プレイヤーが見つからない。
			return false;
		}
	}
	void Enemy_Yellow::ProcessCommonStateTransition()
	{
		//プレイヤーから飛んでいるエネミーに向かうベクトルを計算する。
		Vector3 diff = m_player->GetPosition() - m_position;
		//プレイヤーの少し下を計算する。
		diff.y -= CHASESUBTRACTIONY;
		//もしプレイヤーを見つけていたなら
		if (SearchPlayer() == true)
		{
			//追いかけて移動できるなら
			if (Move == true) {
				//追いかけてくるエネミーからプレイヤーに向かうベクトルを正規化する。
				diff.Normalize();
				//移動速度を設定する。
				m_moveSpeed = diff * MOVEMULTIPLICATION;
				//慣性速度に現在の移動速度を渡しておく。
				m_inertiaSpeed = m_moveSpeed;
			}
			else {
				//発見ステートに遷移する。
				m_EnemyState = enEnemyState_Discovery;
				//移動速度を設定する。
				m_moveSpeed = diff * SEARCHMULTIPLICATION;
				//高さが変わらないようにする。
				m_moveSpeed.y = ZERO;
			}
			return;
		}
		//プレイヤーが見つからないなら
		else
		{
			//慣性速度に0.99を乗算していく
			m_inertiaSpeed *= INERTIAMULTIPLICATION;
			//現在の移動速度に慣性速度を渡しておく。
			m_moveSpeed = m_inertiaSpeed;
			//追いかけて移動できなくする。
			Move = false;
			//待機ステートに遷移する。
			m_EnemyState = enEnemyState_Idle;
		}
	}
	void Enemy_Yellow::ProcessDiscoveryStateTransition()
	{
		//アニメーションの再生が終了したら
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//追いかけて移動できるようにする。
			Move = true;
			//移動ステートに遷移する。
			m_EnemyState = enEnemyState_Move;
		}
	}
	void Enemy_Yellow::ProcessDownStateTransition()
	{
		//当たり判定を削除する。
		m_charaCon.RemoveRigidBoby();
		//アニメーションの再生が終了したら
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//自身を削除する。
			DeleteGO(this);
		}
		return;
	}
	void Enemy_Yellow::ManageState()
	{
		switch (m_EnemyState)
		{
			//待機ステートの時。
		case enEnemyState_Idle:
			//共通のステート遷移処理。
			ProcessCommonStateTransition();
			break;
			//発見ステートの時。
		case enEnemyState_Discovery:
			//発見ステートの遷移処理。
			ProcessDiscoveryStateTransition();
			break;
			//移動ステートの時。
		case enEnemyState_Move:
			//共通のステート遷移処理。
			ProcessCommonStateTransition();
			break;
			//死亡ステートの時。
		case enEnemyState_Down:
			//死亡ステートの遷移処理。
			ProcessDownStateTransition();
			break;
		}
	}
	void Enemy_Yellow::PlayAnimation()
	{
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.2f);
		switch (m_EnemyState)
		{
			//待機ステートの時。
		case enEnemyState_Idle:
			//待機アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//発見ステートの時。
		case enEnemyState_Discovery:
			//アニメーションの再生速度。
			m_modelRender.SetAnimationSpeed(1.0f);
			//発見アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Discovery, 1.0f);
			break;
			//移動ステートの時。
		case enEnemyState_Move:
			//移動アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
			break;
			//死亡ステートの時。
		case enEnemyState_Down:
			//アニメーションの再生速度。
			m_modelRender.SetAnimationSpeed(1.5f);
			//死亡アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Down, 1.0f);
			break;
		default:
			break;
		}
	}
	void Enemy_Yellow::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
	{
		//キーの名前が「Move_Sound」の時。
		if (wcscmp(eventName, L"Move_Sound") == 0)
		{
			//追いかけて移動しているなら
			if (Move == true) {
				//効果音の設定。
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(m_soundlist->ENEMYMOVE2);
				//ループ再生しない。
				se->Play(false);
				//ボリュームの設定。
				se->SetVolume(0.15f);
			}
		}
	}
	void Enemy_Yellow::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}