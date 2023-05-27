#pragma once
#include "IBgActor.h"

/// <summary>
/// 風車クラス
/// </summary>
namespace App {
	class Windmill :public IBgActor
	{
	public:
		Windmill();
		~Windmill();
		bool Start();
		void Update();
		void Render(RenderContext& rc);

	private:
		//風車のアニメーションクリップ
		enum EnAnimationClip {
			enAnimationClip_Move,//回転
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//アニメーションクリップ
	};
}