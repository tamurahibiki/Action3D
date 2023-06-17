#pragma once
#include "InGame/Bg/IBgActor.h"
/// <summary>
/// ���N���X
/// </summary>
namespace App {
	class Bard :public IBgActor
	{
	public:
		//���̃X�e�[�g
		enum EnBardState {
			enBardState_Idle,             //�ҋ@�X�e�[�g
			enBardState_Move              //�ړ��X�e�[�g
		};
	public:
		Bard();
		~Bard();
		bool Start();
		void Update();
		//�ړ�����
		void Move();
		//�A�j���[�V��������
		void PlayAnimation();
		//�X�e�[�g����
		void ManageState();
		void Render(RenderContext& rc);

	private:
		/// <summary>
		/// �v���C���[��T������B
		/// </summary>
		/// <returns>�v���C���[������������true�B</returns>
		const bool SearchPlayer() const;
		/// <summary>
		/// ���ʂ̃X�e�[�g�J�ڏ����B
		/// </summary>
		void ProcessCommonStateTransition();
		/// <summary>
		/// �ړ��X�e�[�g�̑J�ڏ����B
		/// </summary>
		void ProcessMoveStateTransition();
		//���̃A�j���[�V�����N���b�v
		enum EnAnimationClip {
			enAnimationClip_Idle,  //�ҋ@
			enAnimationClip_Move,  //�ړ�
			enAnimationCilp_Num,
		};

		Vector3				  m_moveSpeed;                      //�ړ����x
		AnimationClip         m_animClips[enAnimationCilp_Num]; //�A�j���[�V�����N���b�v
		EnBardState		      m_bardState = enBardState_Idle;   //���̃X�e�[�g
		float			      m_disappearTime = 0.0f;           //���������鎞��
		/// <summary>
		/// �H�΂������ʉ����Đ�����B
		/// </summary>
		/// <returns>�H�΂������ʉ����Đ�����Ȃ�true�B</returns>
		bool                  m_moveSound = true;
	};
}