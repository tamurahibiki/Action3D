#pragma once
#include "IActor.h"
/// <summary>
/// �G�N���X�̊��N���X
/// </summary>
class IEnemy :public IActor
{
public:
    IEnemy() {}  //�R���X�g���N�^
    //�G�l�~�[�̉�]����
    void EnemyRotation();
    //�f�X�g���N�^
    //C++�̏ꍇ�A���N���X�ɂ�virtual���K�v�ł��B
    virtual ~IEnemy() {}
    //�h���N���X����A�N�Z�X�ł���悤��
    //protected�ɂ��Ă����܂��B
protected:
	/// <summary>
	/// �|�����ʉ����Đ�����B
	/// </summary>
	/// <returns>�|�����ʉ����Đ�����Ȃ�true�B</returns>
    bool                DownSound = true;
	/// <summary>
	/// �ǂ������Ĉړ�����B
	/// </summary>
	/// <returns>�ǂ������Ĉړ�����Ȃ�true�B</returns>
    bool                Move = false;
 
    CharacterController m_charaCon;                 //�L�����N�^�[�R���g���[���[
    Vector3             m_moveSpeed;                //�ړ����x
    Vector3             m_inertiaSpeed;             //����
};