#include "stdafx.h"
#include "Fort.h"
#include "Player.h"
#include "Player_Head.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SoundList.h"

namespace
{
	const float SEARCHRANGE  = 600.0f;//探索範囲
	const float FORTVISION   = 360.0f;//視野
	const float HEDADDITIONZ = 400.0f;//プレイヤーの頭モデルの奥行きに加算
	const float HEDADDITIONY = 350.0f;//プレイヤーの頭モデルの高さに加算
}
namespace App {
	Fort::Fort() {}
	Fort::~Fort() {}
	bool Fort::Start()
	{
		//アニメーションを読み込む。
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Fort_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		m_animClips[enAnimationClip_Move].Load("Assets/animData/Fort_Move.tka");
		m_animClips[enAnimationClip_Move].SetLoopFlag(false);
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/gimmick/Fort.tkm", false, true, m_animClips, enAnimationCilp_Num);
		//座標、回転、大きさを設定する。
		SetupTRS();

		//アニメーションイベント用の関数を設定する。
		m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
			OnAnimationEvent(clipName, eventName);
			});

		m_head = FindGO<Player_Head>("player_head");
		m_soundlist = FindGO<SoundList>("soundlist");
		return true;
	}
	void Fort::Update()
	{
		m_player = FindGO<Player>("player");
		//ステートの遷移処理。
		ManageState();
		//アニメーションの再生。
		PlayAnimation();
		//モデルの更新。
		m_modelRender.Update();
	}
	const bool Fort::SearchPlayer() const
	{
		//プレイヤーから大砲に向かうベクトルを計算する。
		Vector3 diff = m_player->GetPosition() - m_position;
		//プレイヤーにある程度近かったら
		if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
		{
			//大砲からプレイヤーに向かうベクトルを正規化する。
			diff.Normalize();
			/*大砲の正面のベクトルと、大砲からプレイヤーに向かうベクトルの
			内積(cosθ)を求める。*/
			float cos = m_forward.Dot(diff);
			//内積(cosθ)から角度(θ)を求める。
			float angle = acosf(cos);
			//角度(θ)が360°より小さければ
			if (angle <= (Math::PI / FORTVISION) * FORTVISION)
			{
				//プレイヤーを見つける。
				return true;
			}
		}
		//プレイヤーが見つからない。
		return false;
	}
	void Fort::ProcessCommonStateTransition()
	{
		//もしプレイヤーを見つけていたなら
		if (SearchPlayer() == true)
		{
			//プレイヤーを描画しない。
			m_player->PlayerNotDraw = true;
			//プレイヤーを大砲まで移動させる。
			m_player->Fort_Idle = true;
			//通常カメラを処理しない。
			m_player->Default = false;
			//奥行きカメラを処理しない。
			m_player->Forward = false;

			//効果音を再生する。
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->FORTIDLE);
			se->Play(false);
			se->SetVolume(0.1f);

			//作動ステートに遷移する。
			m_fortState = enFortState_Move;
			return;
		}
		else
		{
			//待機ステートに遷移する。
			m_fortState = enFortState_Idle;
		}
	}
	void Fort::ProcessMoveStateTransition()
	{
		//アニメーションの再生が終了したら
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			//共通ステートを遷移する。
			ProcessCommonStateTransition();
		}
	}
	void Fort::ManageState()
	{
		//switch文。
		switch (m_fortState)
		{
			//待機ステートの時。
		case enFortState_Idle:
			//共通ステートのステート遷移処理。
			ProcessCommonStateTransition();
			break;
			//作動ステートの時。
		case enFortState_Move:
			//作動ステートのステート遷移処理。
			ProcessMoveStateTransition();
			break;
		}
	}
	void Fort::PlayAnimation()
	{
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.0f);
		//switch文。
		switch (m_fortState) {
			//待機ステートの時。
		case enFortState_Idle:
			//待機アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
			break;
			//作動ステートの時。
		case enFortState_Move:
			//作動アニメーションを再生。
			m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
			break;
		default:
			break;
		}
	}
	void Fort::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
	{
		//キーの名前が「Fort」の時。
		if (wcscmp(eventName, L"Fort") == 0)
		{
			//プレイヤーを大砲から発射する。
			m_player->Fort_Move = true;
			//プレイヤーを大砲まで移動させることを止める。
			m_player->Fort_Idle = false;
			//プレイヤーの頭モデルを削除する。
			DeleteGO(m_head);
		}
		//キーの名前が「Fort2」の時。
		if (wcscmp(eventName, L"Fort2") == 0)
		{
			//効果音を再生する。
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->FORTSTAY);
			se->Play(false);
			se->SetVolume(0.3f);
			//プレイヤーを描画する。
			m_player->PlayerNotDraw = false;
		}
		//キーの名前が「Fort_Hed」の時。
		if (wcscmp(eventName, L"Fort_Hed") == 0)
		{
			//プレイヤーの頭モデルを作成する。
			MakeHead();
		}
	}
	void Fort::MakeHead()
	{
		//プレイヤーの頭モデルを生成する。
		m_head = NewGO<Player_Head>(0, "player_head");
		//座標を設定する。
		Vector3 player_hedPosition = m_position;
		player_hedPosition.z += HEDADDITIONZ;
		player_hedPosition.y += HEDADDITIONY;
		//座標を設定する。
		m_head->SetPosition(player_hedPosition);
	}
	void Fort::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}