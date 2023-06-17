#pragma once
#include "InGame/Bg/IBgActor.h"

/// <summary>
/// 奥行きカメラに変更するポイントクラス
/// </summary>
namespace App {
	class Forward :public IBgActor
	{
	public:
		Forward();
		~Forward();
		bool Start();
		void Update();
	};
}