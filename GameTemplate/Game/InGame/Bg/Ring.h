#pragma once
#include "InGame/Bg/IBgActor.h"

/// <summary>
/// ƒŠƒ“ƒOƒNƒ‰ƒX
/// </summary>
namespace App {
	class Ring :public IBgActor
	{
	public:
		Ring();
		~Ring();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}