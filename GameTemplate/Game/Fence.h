#pragma once
#include "IBgActor.h"
/// <summary>
/// �t�F���X�N���X
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

