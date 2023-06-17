#pragma once
#include"InGame/Bg/IBgActor.h"
/// <summary>
/// ハーフフェンスクラス
/// </summary>
namespace App {
	class FenceHalf :public IBgActor
	{
	public:
		FenceHalf();
		~FenceHalf();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}