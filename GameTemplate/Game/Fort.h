#pragma once
#include "IBgActor.h"
class Player_Head;
/// <summary>
/// ��C�N���X
/// </summary>
class Fort :public IBgActor
{
	//��C�̃X�e�[�g
	enum EnFortState {
		enFortState_Idle,             //�ҋ@�X�e�[�g
		enFortState_Move,             //�쓮�X�e�[�g
	};
public:
	Fort();
	~Fort();
	bool Start();
	void Update();
	void ManageState();  //�X�e�[�g����
	void PlayAnimation();//�A�j���[�V��������
	void MakeHead();      //�v���C���[�̓��𐶐�����B
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
	/// �쓮�X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessMoveStateTransition();
	//�A�j���[�V�����C�x���g�p�̊֐�
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	//��C�̃A�j���[�V�����N���b�v
	enum EnAnimationClip {
		enAnimationClip_Idle,//�ҋ@
		enAnimationClip_Move,//�쓮
		enAnimationCilp_Num,
	};

	AnimationClip       m_animClips[enAnimationCilp_Num];//�A�j���[�V�����N���b�v
	EnFortState		    m_fortState = enFortState_Idle;  //��C�̃X�e�[�g
	Player_Head*         m_head = nullptr;                 //�v���C���[�̓�
	/// <summary>
	/// �v���C���[�̓���`�悷��B
	/// </summary>
	/// <returns>�v���C���[�̓���`�悷��Ȃ�true�B</returns>
	bool Head = true;
};

