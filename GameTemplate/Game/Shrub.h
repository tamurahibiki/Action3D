#pragma once
#include "IBgActor.h"
/// <summary>
/// ’á–ØƒNƒ‰ƒX
/// </summary>
class Shrub :public IBgActor
{
public:
	Shrub();
	~Shrub();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};