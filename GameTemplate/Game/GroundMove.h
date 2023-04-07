#pragma once
#include <CollisionObject.h>
#include"IBgActor.h"
/// <summary>
/// 回転する地面クラス
/// </summary>
class GroundMove :public IBgActor
{
public:
	GroundMove();
	~GroundMove();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};