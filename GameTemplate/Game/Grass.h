#pragma once
#include"IBgActor.h"
/// <summary>
/// ���N���X
/// </summary>
namespace App {
	class Grass :public IBgActor
	{
	public:
		Grass();
		~Grass();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}