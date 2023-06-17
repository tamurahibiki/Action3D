#pragma once
#include"InGame/Bg/IBgActor.h"
/// <summary>
/// ‘å–Cü‚è‚Ì‘•üƒNƒ‰ƒX
/// </summary>
namespace App {
	class GroundRoad :public IBgActor
	{
	public:
		GroundRoad();
		~GroundRoad();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}