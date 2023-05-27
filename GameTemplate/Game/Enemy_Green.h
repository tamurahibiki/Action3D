#pragma once
#include "IEnemy.h"

/// <summary>
/// �������U���G�l�~�[�N���X
/// </summary>
namespace App {
	class Enemy_Green :public IEnemy
	{
		//�������U���G�l�~�[�̃X�e�[�g
		enum EnEnemy_BlueState {
			enEnemyState_Idle,//�ҋ@
			enEnemyState_Attack,//�U��
			enEnemyState_Down//���S
		};
	public:
		Enemy_Green();
		~Enemy_Green();
		bool Start();
		void Update();
		//��]����
		void Rotation();
		//�U��(�C�e)�̍쐬
		void MakeAttack();
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
		/// �U���X�e�[�g�J�ڏ����B
		/// </summary>
		void ProcessAttackStateTransition();
		/// <summary>
		/// ���S�X�e�[�g�J�ڏ����B
		/// </summary>
		void ProcessDownStateTransition();

		//�A�j���[�V�����C�x���g�p�̊֐�
		void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
		//�������U���G�l�~�[�̃A�j���[�V�����N���b�v
		enum EnAnimationClip {
			enAnimationClip_Idle,//�ҋ@
			enAnimationClip_Attack,//�U��
			enAnimationClip_Down,//���S
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//�A�j���[�V�����N���b�v
		EnEnemy_BlueState	m_EnemyState = enEnemyState_Idle;//�������U���G�l�~�[�̃X�e�[�g
	};
}