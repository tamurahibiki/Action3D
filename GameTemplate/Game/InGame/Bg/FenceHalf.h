#pragma once
#include"InGame/Bg/IBgActor.h"
/// <summary>
/// �n�[�t�t�F���X�N���X
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