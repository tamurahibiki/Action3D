#pragma once
#include "InGame/Bg/IBgActor.h"

/// <summary>
/// ���s���J�����ɕύX����|�C���g�N���X
/// </summary>
namespace App {
	class Forward :public IBgActor
	{
	public:
		Forward();
		~Forward();
		bool Start();
		void Update();
	};
}