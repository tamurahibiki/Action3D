#include "stdafx.h"
#include "GoalPoint.h"
#include "CollisionObject.h"
#include "Game.h"
#include "Player.h"
namespace
{
	const float SEARCHRANGE = 600.0f;     //探索範囲
	const float GOALPOINTVISION = 360.0f; //視野
}
namespace App {
	GoalPoint::GoalPoint() {}
	GoalPoint::~GoalPoint() {}
	bool GoalPoint::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/gimmick/GoalPoint.tkm", false, false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		m_game = FindGO<Game>("game");

		return true;
	}
	void GoalPoint::Update()
	{
		m_player = FindGO<Player>("player");
		//もしプレイヤーを見つけていたなら
		if (SearchPlayer() == true)
		{
			//プレイヤーをゴール状態にする。
			m_player->Goal = true;
			//通常カメラを処理しない。
			m_player->Default = false;
			//中間地点到達の処理を削除する。
			m_game->Try = false;
			return;
		}
		//モデルの更新。
		m_modelRender.Update();
	}
	const bool GoalPoint::SearchPlayer() const
	{
		//プレイヤーからゴールポイントに向かうベクトルを計算する。
		Vector3 diff = m_player->GetPosition() - m_position;
		//プレイヤーがある程度近かったら
		if (diff.LengthSq() <= SEARCHRANGE * SEARCHRANGE)
		{
			//ゴールポイントからプレイヤーに向かうベクトルを正規化する。
			diff.Normalize();
			/*ゴールポイントの正面のベクトルと、
			ゴールポイントからプレイヤーに向かうベクトルの
			内積(cosθ)を求める。*/
			float cos = m_forward.Dot(diff);
			//内積(cosθ)から角度(θ)を求める。
			float angle = acosf(cos);
			//角度(θ)が360°より小さければ
			if (angle <= (Math::PI / GOALPOINTVISION) * GOALPOINTVISION)
			{
				//プレイヤーを見つける。
				return true;
			}
		}
		//プレイヤーが見つからない。
		return false;
	}
	void GoalPoint::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}