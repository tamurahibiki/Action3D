#pragma once
#include "InGame/Bg/IBgActor.h"
/// <summary>
/// �ʏ�J�����ɕύX����|�C���g�N���X
/// </summary>
namespace App {
	class Default :public IBgActor
	{
	public:
		Default();
		~Default();
		bool Start();
		void Update();
	};
}