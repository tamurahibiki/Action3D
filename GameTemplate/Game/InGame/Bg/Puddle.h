#pragma once
#include "InGame/Bg/IBgActor.h"

/// <summary>
/// �����܂�N���X
/// </summary>
namespace App {
	class Puddle : public IBgActor
	{
	public:
		Puddle();
		~Puddle();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}