#pragma once
#include "InGame/Bg/IBgActor.h"
namespace App {
	/// <summary>
	/// �ؔ��N���X
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