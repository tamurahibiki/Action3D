#pragma once
#include "InGame/Bg/IBgActor.h"

/// <summary>
/// ��C�ړ��̒��_�|�C���g�N���X
/// </summary>
namespace App {
	class FortTop :public IBgActor
	{
	public:
		FortTop();
		~FortTop();
		bool Start();
		void Update();
	};
}