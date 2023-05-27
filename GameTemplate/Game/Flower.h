#pragma once
#include "IBgActor.h"
/// <summary>
/// 花クラス
/// </summary>
namespace App {
	class Flower :public IBgActor
	{
	public:
		Flower();
		~Flower();
		bool Start();
		void Update();
		void Render(RenderContext& rc);

	private:
		//花のアニメーションクリップ
		enum EnAnimationClip {
			enAnimationClip_Idle,//待機
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//アニメーションクリップ
	};
}