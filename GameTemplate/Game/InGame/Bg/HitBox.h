#pragma once
#include "InGame/Bg/IBgActor.h"

/// <summary>
/// 見えない当たり判定クラス
/// </summary>
namespace App {
	class HitBox :public IBgActor
	{
	public:
		HitBox();
		~HitBox();
		bool Start();
		void Update();
	};
}