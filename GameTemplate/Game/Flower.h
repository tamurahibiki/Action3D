#pragma once
#include "IBgActor.h"
/// <summary>
/// �ԃN���X
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
		//�Ԃ̃A�j���[�V�����N���b�v
		enum EnAnimationClip {
			enAnimationClip_Idle,//�ҋ@
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//�A�j���[�V�����N���b�v
	};
}