#pragma once
#include"InGame/Bg/IBgActor.h"

/// <summary>
/// �v���C���[�̓����f���N���X
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
		//�v���C���[�̓����f���̃A�j���[�V����
		enum EnAnimationClip {
			enAnimationClip_Idle,
			enAnimationCilp_Num,
		};
		Vector3					m_scale = Vector3::One;				//�傫���B
		AnimationClip           m_animClips[enAnimationCilp_Num];   //�A�j���[�V�����N���b�v
	};
}