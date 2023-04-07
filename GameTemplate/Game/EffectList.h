#pragma once
class EffectList:public IGameObject
{
public:
	EffectList();
	~EffectList();
	bool Start();
	
	const int MOVE        = 0; //�_�b�V���ړ��G�t�F�N�g�ԍ�
	const int WALK        = 1; //�����ړ��G�t�F�N�g�ԍ�
	const int DASHFIRST   = 2; //�X�[�p�[�_�b�V�����������G�t�F�N�g�ԍ�
	const int DASHMAX     = 3; //�X�[�p�[�_�b�V���G�t�F�N�g�ԍ�
	const int BLOCK       = 4; //�u���b�N�j��G�t�F�N�g�ԍ�
	const int DMF         = 5; //�ΉԃG�t�F�N�g�ԍ�
	const int JUMP        = 6; //�W�����v�G�t�F�N�g�ԍ�
	const int DROP        = 7; //�q�b�v�h���b�v���n�G�t�F�N�g�ԍ�
	const int DMF2        = 8; //�ł��ՃG�t�F�N�g�ԍ�
	const int ENEMYMOVE   = 9; //�G�l�~�[�ړ��G�t�F�N�g�ԍ�
	const int FORTMOVE    = 10;//��C�ړ��G�t�F�N�g�ԍ�
	const int CLEAR       = 11;//�N���A�G�t�F�N�g�ԍ�
	const int ENEMYDAMAGE = 12;//�G�l�~�[�_���[�W�G�t�F�N�g�ԍ�
};

