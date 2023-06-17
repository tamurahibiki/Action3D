#pragma once
#include "InGame/Enemy/IEnemy.h"

/// <summary>
/// �ǂ������Ă���G�l�~�[�N���X
/// </summary>
namespace App {
	class Enemy_Red :public IEnemy
	{
		//�ǂ������Ă���G�l�~�[�̃X�e�[�g
		enum EnEnemy_RedState {
			enEnemyState_Idle,//�ҋ@
			enEnemyState_Move,//�ړ�
			enEnemyState_Down //���S
		};
	public:
		Enemy_Red();
		~Enemy_Red();
		bool Start();
		void Update();
		//��]����
		void Rotation();
		//�Ǐ]����
		void Chase();
		//�����蔻��
		void Collision();
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
		/// �ҋ@�X�e�[�g�J�ڏ����B
		/// </summary>
		void ProcessIdleStateTransition();
		/// <summary>
		/// ���S�X�e�[�g�J�ڏ����B
		/// </summary>
		void ProcessDownStateTransition();

		//�A�j���[�V�����C�x���g�p�̊֐�
		void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
		//�ǂ������Ă���G�l�~�[�̃A�j���[�V�����N���b�v
		enum EnAnimationClip {
			enAnimationClip_Idle,//�ҋ@
			enAnimationClip_Move,//�ړ�
			enAnimationClip_Down,//���S
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//�A�j���[�V�����N���b�v
		EnEnemy_RedState	m_EnemyState = enEnemyState_Move;//�ǂ������Ă���G�l�~�[�̃X�e�[�g
	};
}