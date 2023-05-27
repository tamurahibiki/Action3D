#include "stdafx.h"
#include "Enemy_Green.h"
#include "Player.h"
#include "Shell.h"
#include "CollisionObject.h"
#include "SoundList.h"

namespace
{   const float  SCALEMULTIPLICATION = 1.5f;    //乗算する大きさ。
	const float  SEARCHRANGE         = 3000.0f; //探索範囲
	const float  GRRENVISION         = 180.0f;  //視野
	const float  CHARACON            = 100.0f;  //当たり判定の半径と高さ
	const float  SHELLADDITIONY      = 180.0f;  //砲弾に加算する高さ
}
namespace App {
	Enemy_Green::Enemy_Green() {}
	Enemy_Green::~Enemy_Green() {}
	bool Enemy_Green::Start()
	{
		//アニメーションを読み込む。
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Enemy_Green_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animClips[enAnimationClip_Attack].Load("Assets/animData/Enemy_Green_Attack.tka");
		m_animClips[enAnimationClip_Attack].SetLoopFlag(false);
		m_animClips[enAnimationClip_Down].Load("Assets/animData/Enemy_Green_Down.tka");
		m_animClips[enAnimationClip_Down].SetLoopFlag(false);
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/enemy/Enemy_Green.tkm", false, false, m_animClips, enAnimationCilp_Num);
		//座標、回転、大きさを設定する。
		m_scale *= SCALEMULTIPLICATION;
		SetupTRS();

		//当たり判定を作成する。
		m_charaCon.Init(
			CHARACON,//半径
			CHARACON,//高さ
			m_position//座標
		);
		//アニメーションイベント用の関数を設定する。
		m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
			OnAnimationEvent(clipName, eventName);
			});
		m_soundlist = FindGO<SoundList>("soundlist");

		return true;
	}
	void Enemy_Green::Update()
	{
		m_player = FindGO<Player>("player");
		//回転処理。
		Rotation();
		//当たり判定。
		Collision();
		//ステートの遷移処理。
		ManageState();
		//アニメーションの再生。
		PlayAnimation();
		//モデルの更新。
		m_modelRender.Update();
	}
	void Enemy_Green::Rotation()
	{
		EnemyRotation();
	}
	void Enemy_Green::MakeAttack()
	{
		//砲弾のオブジェクトを作成する。
		Shell* attack = NewGO<Shell>(0, "shell");
		//座標を設定する。
		Vector3 attackPosition = m_position;
		attackPosition.x += CHARACON;
		attackPosition.y += SHELLADDITIONY;
		attack->SetPosition(attackPosition);
		//回転を設定する。
		attack->SetRotation(m_rotation);
	}
	void Enemy_Green::Collision()
	{
		//プレイヤーの足のコリジョンを所得する。
		const auto& legcollision = g_collisionObjectManager->FindCollisionObjects("Leg");
		//コリジョンの配列をfor文で回す。
		for (auto collision : legcollision)
		{
			//プレイヤーの足のコリジョンと自身の当たり判定が衝突したら
			if (collision->IsHit(m_charaCon))
			{
				//踏み台ジャンプを出来るようにする。
				m_player->JunpCount = true;
				//踏まれた効果音を一度だけ再生する。
				if (DownSound == true)
				{
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(m_soundlist->ENEMYDOWN2);
					se->Play(false);//ループ再生しない。
					se->SetVolume(0.05f);//ボリュームの設定。
					DownSound = false;
				}
				return;
			}
			else
			{
				//プレイヤーが踏み台ジャンプ出来なかったら
				if (m_player->JunpCount == false)
				{
					//踏まれた効果音を再生出来るようにする。
					DownSound = true;
				}
			}
		}
		//プレイヤーのお尻のコリジョンを所得する。
		const auto& hipcollision = g_collisionObjectManager->FindCollisionObjects("Hip");
		//コリジョンの配列をfor文で回す。
		for (auto collision : hipcollision)
		{
			//プレイヤーのお尻のコリジョンと自身の当たり判定が衝突したら
			if (collision->IsHit(m_charaCon))
			{
				//倒れた効果音を一度だけ再生する。
				if (DownSound == true)
				{
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(m_soundlist->ENEMYDOWNHIP);
					se->Play(false);//ループ再生しない。
					se->SetVolume(0.2f);//ボリュームの設定。
					DownSound = false;
				}
				//ダウンステートに遷移する。
				m_EnemyState = enEnemyState_Down;
				return;
			}
		}
	}
	const bool Enemy_Green::SearchPlayer() const
	{
		//プレイヤーが死亡していないなら
		if (m_player->Dead == false)
		{
			//プレイヤーから遠距離攻撃エネミーに向かうベクトルを計算する
			Vector3 diff = m_player->GetPosition() - m_position;
			//プレイヤーにある程度近かったら
			if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
			{
				//遠距離攻撃エネミーからプレイヤーに向かうベクトルを正規化する。
				diff.Normalize();
				/*遠距離攻撃エネミーの正面のベクトルと、
				遠距離攻撃エネミーからプレイヤーに向かうベクトルの
				内積(cosθ)を求める。*/
				float cos = m_forward.Dot(diff);
				//内積(cosθ)から角度(θ)を求める。
				float angle = acosf(cos);
				//角度(θ)が180°より小さければ
				if (angle <= (Math::PI / GRRENVISION) * GRRENVISION)
				{
					//プレイヤーを見つける。
					return true;
				}
			}
			//プレイヤーが見つからない。
			return false;
		}
	}
	void Enemy_Green::ProcessCommonStateTransition()
	{
		//もしプレイヤーを見つけていたなら
		if (SearchPlayer() == true)
		{
			//待機ステートに遷移する。
			m_EnemyState = enEnemyState_Idle;
			return;
		}
		//プレイヤーが見つからないなら
		else
		{
			//待機ステートに遷移する。
			m_EnemyState = enEnemyState_Idle;
		}
	}
	void Enemy_Green::ProcessIdleStateTransition()
	{
		//もしプレイヤーを見つけていたなら
		if (SearchPlayer() == true)
		{
			//攻撃ステートに遷移する。
			m_EnemyState = enEnemyState_Attack;
		}
		else
		{
			//共通ステートのステート遷移処理。
			ProcessCommonStateTransition();
		}
	}
	void Enemy_Green::ProcessAttackStateTransition()
	{
		//アニメーションの再生が終了したら
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//共通ステートのステート遷移処理。
			ProcessCommonStateTransition();
		}
	}
	void Enemy_Green::ProcessDownStateTransition()
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
	void Enemy_Green::ManageState()
	{
		switch (m_EnemyState)
		{
			//待機ステートの時。
		case enEnemyState_Idle:
			//待機ステートのステート遷移処理。
			ProcessIdleStateTransition();
			break;
			//攻撃ステートの時。
		case enEnemyState_Attack:
			//攻撃ステートのステート遷移処理。
			ProcessAttackStateTransition();
			break;
			//死亡ステートの時。
		case enEnemyState_Down:
			//死亡ステートのステート遷移処理。
			ProcessDownStateTransition();
			break;
		}
	}
	void Enemy_Green::PlayAnimation()
	{
		switch (m_EnemyState)
		{
			//待機ステートの時。
		case enEnemyState_Idle:
			//アニメーションの再生速度。
			m_modelRender.SetAnimationSpeed(1.2f);
			//待機アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//攻撃ステートの時。
		case enEnemyState_Attack:
			//アニメーションの再生速度。
			m_modelRender.SetAnimationSpeed(0.3f);
			//攻撃アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Attack, 1.0f);
			break;
			//死亡ステートの時。
		case enEnemyState_Down:
			//アニメーションの再生速度。
			m_modelRender.SetAnimationSpeed(1.1f);
			//死亡アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Down, 1.0f);
			break;
		default:
			break;
		}
	}
	void Enemy_Green::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
	{
		//キーの名前が「Attack」の時。
		if (wcscmp(eventName, L"Attack") == 0)
		{
			//砲弾を作成する。
			MakeAttack();
		}
	}
	void Enemy_Green::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}