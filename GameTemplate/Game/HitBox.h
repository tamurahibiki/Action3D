#pragma once
#include "IBgActor.h"
/// <summary>
/// �����Ȃ������蔻��N���X
/// </summary>
class HitBox :public IBgActor
{
public:
	HitBox();
	~HitBox();
	bool Start();
	void Update();
};