#pragma once
#include "InGame/Bg/IBgActor.h"

/// <summary>
/// �����Ȃ������蔻��N���X
/// </summary>
namespace App {
	class HitBox :public IBgActor
	{
	public:
		HitBox();
		~HitBox();
		bool Start();
		void Update();
	};
}