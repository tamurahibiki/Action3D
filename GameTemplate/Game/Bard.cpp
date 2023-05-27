#include "stdafx.h"
#include "Bard.h"
#include "Player.h"
#include "SoundList.h"
namespace 
{
	const float  SEARCHRANGE          = 800.0f;//探索範囲
	const float  BARDVISION           = 360.0f;//視野
	const float  DISAPPEARTIMEMAX     = 4.0f;  //鳥が消えるまでの時間
	const float  FIRSTMULTIPLICATION  = 10.0f; //最初に乗算する速度
	const float  SECONDMULTIPLICATION = 5.0f;  //次に乗算する速度
}
namespace App {
	Bard::Bard() {}
	Bard::~Bard() {}
	bool Bard::Start()
	{
		//アニメーションを読み込む。
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Bard_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animClips[enAnimationClip_Move].Load("Assets/animData/Bard_Move.tka");
		m_animClips[enAnimationClip_Move].SetLoopFlag(true);

		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Bard.tkm", false,false, m_animClips, enAnimationCilp_Num);
		//座標、回転、大きさを設定する。
		SetupTRS();

		m_soundlist = FindGO<SoundList>("soundlist");
		return true;
	}
	void Bard::Update()
	{
		m_player = FindGO<Player>("player");
		//ステートの遷移処理。
		ManageState();
		//アニメーションの再生。
		PlayAnimation();
		//モデルの更新。
		m_modelRender.Update();
	}
	void Bard::Move()
	{
		//YZ方向に移動方向を設定する。
		m_moveSpeed = Vector3::AxisYZ;
		//YZ方向に回転。
		m_rotation.Apply(m_moveSpeed);
		//座標の移動。
		m_position += m_moveSpeed * FIRSTMULTIPLICATION;
		m_moveSpeed *= SECONDMULTIPLICATION;
		//座標を移動させる。
		m_position += m_moveSpeed;
		//座標を設定する。
		m_modelRender.SetPosition(m_position);
	}
	const bool Bard::SearchPlayer() const
	{
		//プレイヤーから鳥に向かうベクトルを計算する。
		Vector3 diff = m_player->GetPosition() - m_position;
		//プレイヤーにある程度近かったら
		if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
		{
			//鳥からプレイヤーに向かうベクトルを正規化する。
			diff.Normalize();
			/*鳥の正面のベクトルと、鳥からプレイヤーに向かうベクトルの
			内積(cosθ)を求める。*/
			float cos = m_forward.Dot(diff);
			//内積(cosθ)から角度(θ)を求める。
			float angle = acosf(cos);
			//角度(θ)が360°より小さければ
			if (angle <= (Math::PI / BARDVISION) * BARDVISION)
			{
				//プレイヤーを見つける。
				return true;
			}
		}
		//プレイヤーが見つからない。
		return false;
	}
	void Bard::ProcessCommonStateTransition()
	{
		//もしプレイヤーを見つけていたなら
		if (SearchPlayer() == true)
		{
			//移動ステートに遷移する。
			m_bardState = enBardState_Move;
			return;
		}
		//プレイヤーが見つからないなら
		else
		{
			//待機ステートに遷移する。
			m_bardState = enBardState_Idle;
		}
	}
	void Bard::ProcessMoveStateTransition()
	{
		//羽ばたく音を一度だけ再生する。
		if (m_moveSound == true) {
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->BARDMOVE);
			se->Play(false);//ループ再生をしない。
			se->SetVolume(0.15f);//ボリューム
			m_moveSound = false;
		}
		//移動処理。
		Move();
		//鳥が消えるまでの時間をカウントする。
		m_disappearTime += g_gameTime->GetFrameDeltaTime();
		//4秒経つと
		if (m_disappearTime > DISAPPEARTIMEMAX)
		{
			//自信を削除する。
			DeleteGO(this);
		}
	}
	void Bard::ManageState()
	{
		switch (m_bardState)
		{
			//待機ステートの時。
		case enBardState_Idle:
			//共通ステートのステート遷移処理。
			ProcessCommonStateTransition();
			break;
			//移動ステートの時。
		case enBardState_Move:
			//移動ステートのステート遷移処理。
			ProcessMoveStateTransition();
			break;
		}
	}
	void Bard::PlayAnimation()
	{
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.2f);
		switch (m_bardState)
		{
			//待機ステートの時。
		case enBardState_Idle:
			//待機アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//移動ステートの時。
		case enBardState_Move:
			//移動アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
			break;
		default:
			break;
		}
	}
	void Bard::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}