#pragma once
#include"IBgActor.h"

/// <summary>
/// ‘å‚«‚ÈÎƒNƒ‰ƒX
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