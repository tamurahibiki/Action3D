#pragma once
#include "IBgActor.h"
/// <summary>
/// フェンスクラス
/// </summary>
class Fence :public IBgActor
{
public:
	Fence();
	~Fence();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};

