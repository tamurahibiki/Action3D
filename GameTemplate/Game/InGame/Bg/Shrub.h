#pragma once
#include "InGame/Bg/IBgActor.h"
/// <summary>
/// ��؃N���X
/// </summary>
namespace App {
	class Shrub :public IBgActor
	{
	public:
		Shrub();
		~Shrub();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}