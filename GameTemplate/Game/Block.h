#pragma once
#include <CollisionObject.h>
#include "IBgActor.h"

/// <summary>
/// ブロッククラス
/// </summary>
namespace App {
	class Block :public IBgActor
	{
	public:
		Block();
		~Block();
		bool Start();
		void Update();
		//当たり判定。
		void Collision();
		//衝突後の処理。
		void CollisionEstablishment();
		void Render(RenderContext& rc);
	};
}