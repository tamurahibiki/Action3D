#pragma once
#include "IBgActor.h"
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