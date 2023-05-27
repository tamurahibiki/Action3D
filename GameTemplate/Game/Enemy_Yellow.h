#pragma once
#include "IEnemy.h"

/// <summary>
/// ���ł���G�l�~�[�N���X
/// </summary>
namespace App {
	class Enemy_Yellow :public IEnemy
	{
		//���ł���G�l�~�[�̃X�e�[�g
		enum EnEnemy_BlueState {
			enEnemyState_Idle,     //�ҋ@	
			enEnemyState_Discovery,//����
			enEnemyState_Move,     //�ړ�
			enEnemyState_Down      //���S
		};
	public:
		Enemy_Yellow();
		~Enemy_Yellow();
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
		/// �����X�e�[�g�J�ڏ����B
		/// </summary>
		void ProcessDiscoveryStateTransition();
		/// <summary>
		/// ���S�X�e�[�g�J�ڏ����B
		/// </summary>
		void ProcessDownStateTransition();
		//�A�j���[�V�����C�x���g�p�̊֐�
		void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
		//���ł���G�l�~�[�̃A�j���[�V�����N���b�v
		enum EnAnimationClip {
			enAnimationClip_Idle,     //�ҋ@
			enAnimationClip_Discovery,//����
			enAnimationClip_Move,     //�ړ�
			enAnimationClip_Down,     //���S
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//�A�j���[�V�����N���b�v
		EnEnemy_BlueState	m_EnemyState = enEnemyState_Idle;//���ł���G�l�~�[�̃X�e�[�g
	};
}