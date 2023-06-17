#pragma once
#include "InGame/Bg/IBgActor.h"

/// <summary>
/// 大砲移動の頂点ポイントクラス
/// </summary>
namespace App {
	class FortTop :public IBgActor
	{
	public:
		FortTop();
		~FortTop();
		bool Start();
		void Update();
	};
}