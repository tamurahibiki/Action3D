#pragma once
#include"InGame/Bg/IBgActor.h"
/// <summary>
/// �ؐ��̓��N���X
/// </summary>
namespace App {
	class Wood_Road :public IBgActor
	{
	public:
		Wood_Road();
		~Wood_Road();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}