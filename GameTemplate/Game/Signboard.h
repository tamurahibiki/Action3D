#pragma once
#include "IBgActor.h"
/// <summary>
/// �ŔN���X
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