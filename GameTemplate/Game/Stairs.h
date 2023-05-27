#pragma once
#include "IBgActor.h"
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