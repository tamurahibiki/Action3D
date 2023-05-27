#pragma once
#include"IBgActor.h"

/// <summary>
/// 地形クラス
/// </summary>
namespace App {
	class Ground :public IBgActor
	{
	public:
		Ground();
		~Ground();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}