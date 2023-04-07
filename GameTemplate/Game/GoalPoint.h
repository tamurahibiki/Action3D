#pragma once
#include <CollisionObject.h>
#include "IBgActor.h"
class Game;
class Player;
/// <summary>
/// ゴールポイントクラス
/// </summary>
class GoalPoint :public IBgActor
{
public:
	GoalPoint();
	~GoalPoint();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	
private:
	/// <summary>
	/// プレイヤーを探索する。
	/// </summary>
	/// <returns>プレイヤーが見つかったらtrue。</returns>
	const bool SearchPlayer() const;
	Game*                m_game = nullptr;          //ゲーム
};