#include "stdafx.h"
#include "Pebble.h"
#include "InGame/Player/Player.h"

namespace
{
	const float SEARCHRANGE = 200.0f;       //探索範囲
	const float PEBBLEVISION = 360.0f;      //視野
	const float FIRSTMULTIPLICATION = 5.0f; //最初に乗算する速度
	const float SECONDMULTIPLICATION = 4.0f;//次に乗算する速度
}
namespace App {
	Pebble::Pebble() {}
	Pebble::~Pebble() {}

	bool Pebble::Start()
	{
		//アニメーションを読み込む。
		m_animationClips[enAnimationClip_Idle].Load("Assets/animData/Pebble_Idle.tka");
		m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animationClips[enAnimationClip_Move].Load("Assets/animData/Pebble.tka");
		m_animationClips[enAnimationClip_Move].SetLoopFlag(false);

		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Pebble.tkm", false,m_animationClips, enAnimationClip_Num);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Pebble::Update()
	{
		m_player = FindGO<Player>("player");

		//ステートの遷移処理。
		ManageState();
		//アニメーションの再生。
		PlayAnimation();
		//モデルの更新。
		m_modelRender.Update();
	}
	void Pebble::Move()
	{
		//Z方向に移動方向を設定する。
		m_moveSpeed = Vector3::AxisZ;
		//小石の移動方向を決められるなら
		if (PebbleRot == true)
		{
			//プレイヤーの回転と小石の回転を同じにする。
			m_playerrotation = m_player->GetRotation();
			//小石の移動方向を決められなくする。
			PebbleRot = false;
		}
		//Z方向に回転。
		m_playerrotation.Apply(m_moveSpeed);
		//座標の移動
		m_position += m_moveSpeed * 5.0f;
		m_moveSpeed *= 4.0f;
		//座標を移動させる。
		m_position += m_moveSpeed;
		//座標を設定する。
		m_modelRender.SetPosition(m_position);
	}
	const bool Pebble::SearchPlayer() const
	{
		//プレイヤーから小石に向かうベクトルを計算する。
		Vector3 diff = m_player->GetPosition() - m_position;
		//プレイヤーにある程度近かったら
		if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
		{
			//小石からプレイヤーに向かうベクトルを正規化する。
			diff.Normalize();
			/*小石の正面のベクトルと、小石からプレイヤーに向かうベクトルの
			内積(cosθ)を求める。*/
			float cos = m_forward.Dot(diff);
			//内積(cosθ)から角度(θ)を求める。
			float angle = acosf(cos);
			//角度(θ)が360°より小さければ
			if (angle <= (Math::PI / PEBBLEVISION) * PEBBLEVISION)
			{
				//プレイヤーを見つける。
				return true;
			}
		}
		//プレイヤーが見つからない。
		return false;
	}
	void Pebble::ProcessCommonStateTransition()
	{
		//もしプレイヤーを見つけていたなら
		if (SearchPlayer() == true)
		{
			//移動ステートに遷移する。
			m_pebbleState = enPebbleState_Move;
			return;
		}
		//プレイヤーが見つからないなら
		else
		{
			//待機ステートに遷移する。
			m_pebbleState = enPebbleState_Idle;
		}
	}
	void Pebble::ProcessMoveStateTransition()
	{
		//移動処理。
		Move();
		//アニメーションの再生が終了したら
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//小石の移動方向を決められるようにする。
			PebbleRot = true;
			//小石を削除する。
			DeleteGO(this);
		}
	}
	void Pebble::ManageState()
	{
		switch (m_pebbleState)
		{
			//待機ステートの時。
		case enPebbleState_Idle:
			//共通ステートのステート遷移処理。
			ProcessCommonStateTransition();
			break;
			//移動ステートの時。
		case enPebbleState_Move:
			//移動ステートのステート遷移処理。
			ProcessMoveStateTransition();
			break;
		}
	}
	void Pebble::PlayAnimation()
	{
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.2f);
		switch (m_pebbleState)
		{
			//待機ステートの時。
		case enPebbleState_Idle:
			//待機アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//移動ステートの時。
		case enPebbleState_Move:
			//移動アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
			break;
		default:
			break;
		}
	}
	void Pebble::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}