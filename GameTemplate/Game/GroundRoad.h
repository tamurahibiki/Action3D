#pragma once
#include"IBgActor.h"
/// <summary>
/// ��C����̑����N���X
/// </summary>
class GroundRoad :public IBgActor
{
public:
	GroundRoad();
	~GroundRoad();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};