#pragma once
#include <CollisionObject.h>
#include"InGame/Bg/IBgActor.h"

/// <summary>
/// ��]����n�ʃN���X
/// </summary>
namespace App {
	class GroundMove :public IBgActor
	{
	public:
		GroundMove();
		~GroundMove();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}