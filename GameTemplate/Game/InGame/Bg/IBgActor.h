#pragma once
#include "InGame/IActor.h"
/// <summary>
/// �w�i���f���̊��N���X
/// </summary>
namespace App {
	class IBgActor :public IActor
	{
	public:
		IBgActor() {}  //�R���X�g���N�^
		//�f�X�g���N�^
		//C++�̏ꍇ�A���N���X�ɂ�virtual���K�v�ł��B
		virtual ~IBgActor() {}
		//�h���N���X����A�N�Z�X�ł���悤��
		//protected�ɂ��Ă����܂��B
	protected:
		PhysicsStaticObject   m_physicsStaticObject;      //�ÓI�����I�u�W�F�N�g
	};
}