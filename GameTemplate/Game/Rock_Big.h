#pragma once
#include"IBgActor.h"

/// <summary>
/// �傫�Ȑ΃N���X
/// </summary>
namespace App {
	class Rock_Big :public IBgActor
	{
	public:
		Rock_Big();
		~Rock_Big();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
	};
}