#pragma once
#include "IBgActor.h"
/// <summary>
/// ��C�ړ��̒��_�|�C���g�N���X
/// </summary>
class FortTop :public IBgActor
{
public:
	FortTop();
	~FortTop();
	bool Start();
	void Update();
};