#pragma once
#include "IBgActor.h"
/// <summary>
/// �؃N���X
/// </summary>
class Tree :public IBgActor
{
public:
	Tree();
	~Tree();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
};