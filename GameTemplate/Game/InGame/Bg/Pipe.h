#pragma once
#include "InGame/Bg/IBgActor.h"

/// <summary>
/// �y�ǃN���X
/// </summary>
namespace App {
	class Pipe :public IBgActor
	{
	public:
		Pipe();
		~Pipe();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}