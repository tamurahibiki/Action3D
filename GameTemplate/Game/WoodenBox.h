#pragma once
#include "IBgActor.h"
namespace App {
	/// <summary>
	/// –Ø” ƒNƒ‰ƒX
	/// </summary>
	class WoodenBox :public IBgActor
	{
	public:
		WoodenBox();
		~WoodenBox();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}