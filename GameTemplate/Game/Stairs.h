#pragma once
#include "IBgActor.h"
/// <summary>
/// �K�i�N���X
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