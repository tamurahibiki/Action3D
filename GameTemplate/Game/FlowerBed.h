#pragma once
#include"IBgActor.h"
/// <summary>
/// �Ԓd�N���X
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