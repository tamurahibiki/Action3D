#pragma once
#include "InGame/Bg/IBgActor.h"
/// <summary>
/// –ØƒNƒ‰ƒX
/// </summary>
namespace App {
	class Tree :public IBgActor
	{
	public:
		Tree();
		~Tree();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}