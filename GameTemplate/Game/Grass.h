#pragma once
#include"IBgActor.h"
/// <summary>
/// ‘ƒNƒ‰ƒX
/// </summary>
class Grass :public IBgActor
{
public:
	Grass();
	~Grass();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};