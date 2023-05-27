#pragma once
#include "IBgActor.h"

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