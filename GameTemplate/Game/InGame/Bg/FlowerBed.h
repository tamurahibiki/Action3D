#pragma once
#include"InGame/Bg/IBgActor.h"
/// <summary>
/// �Ԓd�N���X
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