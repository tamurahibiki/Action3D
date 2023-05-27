#pragma once
#include "IBgActor.h"

/// <summary>
/// ìyä«ÉNÉâÉX
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