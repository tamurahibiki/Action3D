#pragma once
#include <CollisionObject.h>
#include"InGame/Bg/IBgActor.h"

/// <summary>
/// 回転する地面クラス
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