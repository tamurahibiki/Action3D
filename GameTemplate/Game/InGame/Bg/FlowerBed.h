#pragma once
#include"InGame/Bg/IBgActor.h"
/// <summary>
/// ‰Ô’dƒNƒ‰ƒX
/// </summary>
namespace App {
	class FlowerBed :public IBgActor
	{
	public:
		FlowerBed();
		~FlowerBed();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}