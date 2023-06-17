#pragma once
#include"InGame/Bg/IBgActor.h"

/// <summary>
/// プレイヤーの頭モデルクラス
/// </summary>
namespace App {
	class Player_Head :public IBgActor
	{
	public:
		Player_Head();
		~Player_Head();
		bool Start();
		void Update();
		void Render(RenderContext& rc);

	private:
		//プレイヤーの頭モデルのアニメーション
		enum EnAnimationClip {
			enAnimationClip_Idle,
			enAnimationCilp_Num,
		};
		Vector3					m_scale = Vector3::One;				//大きさ。
		AnimationClip           m_animClips[enAnimationCilp_Num];   //アニメーションクリップ
	};
}