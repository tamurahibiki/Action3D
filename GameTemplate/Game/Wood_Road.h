#pragma once
#include"IBgActor.h"
/// <summary>
/// –Ø»‚Ì“¹ƒNƒ‰ƒX
/// </summary>
namespace App {
	class Wood_Road :public IBgActor
	{
	public:
		Wood_Road();
		~Wood_Road();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}