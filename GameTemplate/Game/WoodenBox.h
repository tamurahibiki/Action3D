#pragma once
#include "IBgActor.h"
/// <summary>
/// �ؔ��N���X
/// </summary>
class WoodenBox :public IBgActor
{
public:
	WoodenBox();
	~WoodenBox();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};