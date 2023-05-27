#pragma once
#include "IBgActor.h"
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