#include "stdafx.h"
#include "Forward.h"
#include "Player.h"
namespace
{
	const float  SEARCHRANGE = 800.0f;//探索範囲
}
namespace App {
	Forward::Forward() {}
	Forward::~Forward() {}
	bool Forward::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/Box.tkm", true, false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Forward::Update()
	{
		m_player = FindGO<Player>("player");
		//モデルを更新。
		m_modelRender.Update();
		//プレイヤーから通常カメラに変更するポイントに向かうベクトルを計算する。
		Vector3 diff = m_player->GetPosition() - m_position;
		//プレイヤーにある程度近かったら
		if (diff.Length() <= SEARCHRANGE)
		{
			//プレイヤーの移動方向を維持する。
			if (m_player->Forward == false) {
				m_player->EnableUsingLastFrameMoveDirection();
			}
			//奥行きカメラに変更する。
			m_player->Default = false;
			//通常カメラを処理しない。
			m_player->Forward = true;
		}
	}
}