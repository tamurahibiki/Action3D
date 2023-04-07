#pragma once
#include "IBgActor.h"
/// <summary>
/// 通常カメラに変更するポイントクラス
/// </summary>
class Default :public IBgActor
{
public:
	Default();
	~Default();
	bool Start();
	void Update();
};