#pragma once
#include "IBgActor.h"
/// <summary>
/// ���΃N���X
/// </summary>
class Pebble : public IBgActor
{
public:
	//���΂̃X�e�[�g
	enum EnPebbleState
	{
		enPebbleState_Idle,//�ҋ@�X�e�[�g
		enPebbleState_Move //�ړ��X�e�[�g
	};
public:
	Pebble();
	~Pebble();
	bool Start();
	void Update();
	void Move();         //�ړ�����
	void PlayAnimation();//�A�j���[�V��������
	void ManageState();  //�X�e�[�g����
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
     //���΂̃A�j���[�V����
	enum EnAnimationClip {		
		enAnimationClip_Idle,//�ҋ@
		enAnimationClip_Move,//�ړ�
		enAnimationClip_Num,
	};

	Vector3		    m_moveSpeed;						  //�ړ����x�B
	AnimationClip	m_animationClips[enAnimationClip_Num];//�A�j���[�V�����N���b�v
	Quaternion      m_playerrotation;                     //�v���C���[�̉�]
	EnPebbleState   m_pebbleState = enPebbleState_Idle;   //���΂̃X�e�[�g
	/// <summary>
	/// ���΂̈ړ����������߂�B
	/// </summary>
	/// <returns>���΂̈ړ����������߂���Ȃ�true�B</returns>
	bool PebbleRot = true;
};