#pragma once
#include "IBgActor.h"
/// <summary>
/// �����O�N���X
/// </summary>
class Ring:public IBgActor
{
public:
	Ring();
	~Ring();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};