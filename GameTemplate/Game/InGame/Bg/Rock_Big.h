#pragma once
#include"InGame/Bg/IBgActor.h"

/// <summary>
/// 大きな石クラス
/// </summary>
namespace App {
	class Rock_Big :public IBgActor
	{
	public:
		Rock_Big();
		~Rock_Big();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}