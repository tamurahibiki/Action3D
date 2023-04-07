#pragma once
#include "IBgActor.h"
/// <summary>
/// ŠÅ”ÂƒNƒ‰ƒX
/// </summary>
class Signboard :public IBgActor
{
public:
	Signboard();
	~Signboard();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};