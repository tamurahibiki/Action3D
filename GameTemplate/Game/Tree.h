#pragma once
#include "IBgActor.h"
/// <summary>
/// �؃N���X
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