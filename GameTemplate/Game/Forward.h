#pragma once
#include "IBgActor.h"
/// <summary>
/// ���s���J�����ɕύX����|�C���g�N���X
/// </summary>
class Forward :public IBgActor
{
public:
	Forward();
	~Forward();
	bool Start();
	void Update();
};