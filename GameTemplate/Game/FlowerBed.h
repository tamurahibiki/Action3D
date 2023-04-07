#pragma once
#include"IBgActor.h"
/// <summary>
/// ‰Ô’dƒNƒ‰ƒX
/// </summary>
class FlowerBed :public IBgActor
{
public:
	FlowerBed();
	~FlowerBed();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};