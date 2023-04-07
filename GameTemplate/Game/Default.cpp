#include "stdafx.h"
#include "Default.h"
#include "Player.h"
namespace
{
	const float SEARCHRANGE = 800.0f;//探索範囲
}

Default::Default() {}
Default::~Default() {}
bool Default::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/Box.tkm", true);
	//座標、回転、大きさを設定する。
	SetupTRS();
	
	return true;
}
void Default::Update()
{
	m_player = FindGO<Player>("player");
	//モデルの更新。
	m_modelRender.Update();

	//プレイヤーから通常カメラに変更するポイントに向かうベクトルを計算する。
	Vector3 diff = m_player->GetPosition() - m_position;
	//プレイヤーにある程度近かったら
	if (diff.Length() <= SEARCHRANGE)
	{
		//プレイヤーの移動方向を維持する。
		if (m_player->Default == false) {
			m_player->EnableUsingLastFrameMoveDirection();
		}
		//通常カメラに変更する。
		m_player->Default = true;
		//奥行きカメラを処理しない。
		m_player->Forward = false;
	}
}