#pragma once
#include "InGame/Bg/IBgActor.h"
/// <summary>
/// フェンスクラス
/// </summary>
namespace App {
	class Fence :public IBgActor
	{
	public:
		Fence();
		~Fence();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}