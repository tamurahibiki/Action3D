#pragma once
#include"IBgActor.h"
/// <summary>
/// ‘å–Cü‚è‚Ì‘•üƒNƒ‰ƒX
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