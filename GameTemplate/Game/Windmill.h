#pragma once
#include "IBgActor.h"

/// <summary>
/// ���ԃN���X
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
		//���Ԃ̃A�j���[�V�����N���b�v
		enum EnAnimationClip {
			enAnimationClip_Move,//��]
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//�A�j���[�V�����N���b�v
	};
}