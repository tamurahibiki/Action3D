#pragma once
#include <CollisionObject.h>
#include"IBgActor.h"
/// <summary>
/// ��]����n�ʃN���X
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