#pragma once
#include "IBgActor.h"

/// <summary>
/// Œ©‚¦‚È‚¢“–‚½‚è”»’èƒNƒ‰ƒX
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