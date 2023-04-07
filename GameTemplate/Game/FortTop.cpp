#include "stdafx.h"
#include "FortTop.h"
#include "Player.h"
namespace
{
	const float SEARCHRANGE = 800.0f;//探索範囲
}
FortTop::FortTop() {}
FortTop::~FortTop() {}

bool FortTop::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/Box.tkm", true);
	//座標、回転、大きさを設定する。
	SetupTRS();
	return true;
}
void FortTop::Update()
{
	m_player = FindGO<Player>("player");
	//モデルの更新。
	m_modelRender.Update();
	//プレイヤーから大砲移動の頂点ポイントポイントに向かうベクトルを計算する。
	Vector3 diff = m_player->GetPosition() - m_position;
	//プレイヤーにある程度近かったら
	if (diff.Length() <= SEARCHRANGE)
	{
		//大砲移動時上昇カメラを処理しない。
		m_player->Fort_Move = false;
		//大砲移動時下降カメラに変更する。
		m_player->Fort_Top = true;
	}
}