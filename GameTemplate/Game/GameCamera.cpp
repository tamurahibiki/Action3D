#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "GoalPoint.h"
#include "Game.h"

namespace
{
	const float DEFAULTTARGETY = 600.0f;        //ターゲットの600.0f上を見る。
	const float GOALTARGETY = 400.0f;           //ターゲットの400.0f上を見る。
	const float GOALPOSMULTIPLICATION = 1500.0f;//ターゲットから1500.0f離れる。

	//////////////////////////////////////
	//ここから使用している関数の大文字を取って名称を付ける。
	//////////////////////////////////////
	//Default,ForWardの注視点から視点までのベクトル。
	const Vector3 DFWPOS = { 2000.0f, 500.0f, 0.0f };
	//FortStayの注視点から視点までのベクトル。
	const Vector3 FSPOS = { 2000.0f, 1000.0f, 0.0f };
	//FortMoveFallの注視点から視点までのベクトル。
	const Vector3 FMFPOS = { 1750.0f, 1000.0f, 0.0f };
	//FortMoveUp,Goalの注視点から視点までのベクトル。
	const Vector3 FMUGPOS = { 1100.0f, 1000.0f, 0.0f };
	//Deadの注視点から視点までのベクトル。
	const Vector3 DPOS = { 10.0f, 1500.0f, 0.0f };
	//Default.FortStay,FortMoveUp,FortMoveFallの回転角度。
	const float DFSFMUFMFROT = 90.0f;
	//ForWardの回転角度。
	const float FWROT = 45.0f;
	//////////////////////////////////////
	//使用している関数の大文字を取って名称を付けるのはここまで。
	//////////////////////////////////////
}
GameCamera::GameCamera(){}
GameCamera::~GameCamera(){}
bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");
	m_goal = FindGO<GoalPoint>("goalpoint");
	m_game = FindGO<Game>("game");
	return true;
}
void GameCamera::DefaultUpdatePositionAndTarget()
{
	//カメラを更新。
	//注視点を計算する。
	Vector3 target= m_player->GetPosition();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += DEFAULTTARGETY;
	//視点を計算する。
	Vector3 pos;
	pos = target + m_toCameraPos;
	//カメラの処理。	
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
}
void GameCamera::GoalUpdatePositionAndTarget()
{
	//カメラを更新。
	//注視点を計算する.
	Vector3 target = m_player->GetPosition();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += GOALTARGETY;
	//プレイヤーとゴールポイントのベクトルを減算する。
	Vector3 V = m_player->GetPosition()-m_goal->GetPosition();
	//Y軸は考慮しない。
	V.y = 0;
	//正規化する。
	V.Normalize();
	//視点を計算する。
	Vector3 pos = target + V * GOALPOSMULTIPLICATION;
	//プレイヤーがジャンプしていなければ
	if (m_player->PlayerJunp == false)
	{
		//カメラの処理。
		g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);
	}
}
void GameCamera::Update()
{
	//プレイヤーが死亡しているなら
	if (m_player->Dead==true)
	{
		//死亡時のカメラアングルに変更する。
		DeadCamera();	
		//視点と注視点を更新する。
		DefaultUpdatePositionAndTarget();
	}

	//プレイヤーが生きていて
	else
	{
		//プレイヤーが大砲に移動しているなら
		if (m_player->Fort_Idle == true &&
			m_player->Fort_Move == false)
		{
			//大砲発射前のカメラアングルに変更する。
			FortStayCamera();
			//視点と注視点を更新する。
			DefaultUpdatePositionAndTarget();
		}
		//プレイヤーが大砲から発射されているなら
		if (m_player->Fort_Idle == false &&
			m_player->Fort_Move == true)
		{
			//大砲移動時上昇のカメラアングルに変更する。
			FortMoveUpCamera();
			//視点と注視点を更新する。
			DefaultUpdatePositionAndTarget();
		}
		//プレイヤーが大砲移動の頂点ポイントにいるなら
		if (m_player->Fort_Top == true)
		{
			//大砲移動時下降のカメラアングルに変更する。
			FortMoveFallCamera();
			//視点と注視点を更新する。
			DefaultUpdatePositionAndTarget();
		}
		//プレイヤーがゴールしているなら
		if (m_player->Goal == true)
		{
			//ゴール時のカメラアングルに変更する。
			GoalCamera();
			//ゴール時の視点と注視点を更新する。
			GoalUpdatePositionAndTarget();
		}
		//プレイヤーが奥行きカメラに変更するポイントにいるなら
		if (m_player->Forward == true)
		{
			//奥行きが分かるカメラアングルに変更する。
			ForWardCamera();
			//視点と注視点を更新する。
			DefaultUpdatePositionAndTarget();
		}
		//プレイヤーが通常カメラに変更するポイントにいるなら
		if (m_player->Default == true)
		{
			//通常のカメラアングルに変更する。
			DefaultCamera();
			//視点と注視点を更新する。
			DefaultUpdatePositionAndTarget();
		}
	}
}
void GameCamera::DefaultCamera()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(DFWPOS);
	//中間地点に到達していたら
	if (m_game->Try == true)
	{
	  //カメラを90°回転させる。
      Quaternion qRot;
	  qRot.SetRotationDeg(Vector3::AxisY, DFSFMUFMFROT);
	  qRot.Apply(m_toCameraPos);
	}
}
void GameCamera::ForWardCamera()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(DFWPOS);
	//カメラを45°回転させる。
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, FWROT);
	qRot.Apply(m_toCameraPos);
}
void GameCamera::FortStayCamera()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(FSPOS);
	//カメラを-90°回転させる。
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, -DFSFMUFMFROT);
	qRot.Apply(m_toCameraPos);
}
void GameCamera::FortMoveUpCamera()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(FMUGPOS);
	//カメラを90°回転させる。
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, DFSFMUFMFROT);
	qRot.Apply(m_toCameraPos);
}
void GameCamera::FortMoveFallCamera()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(FMFPOS);
	//カメラを90°回転させる。
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, DFSFMUFMFROT);
	qRot.Apply(m_toCameraPos);
}
void GameCamera::GoalCamera()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(FMUGPOS);
}
void GameCamera::DeadCamera()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(DPOS);
}