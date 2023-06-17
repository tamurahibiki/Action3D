#pragma once
#include "InGame/Bg/IBgActor.h"
/// <summary>
/// ŠK’iƒNƒ‰ƒX
/// </summary>
namespace App {
	class Stairs :public IBgActor
	{
	public:
		Stairs();
		~Stairs();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}