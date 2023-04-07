#pragma once
class SoundList :public IGameObject
{
public:
	SoundList();
	~SoundList();
	bool Start();

	const int DASH           = 0; //�_�b�V���T�E���h�ԍ�
	const int WALK           = 1; //�����T�E���h�ԍ�
	const int DASHFIRST      = 2; //�X�[�p�[�_�b�V�����������T�E���h�ԍ�
	const int DASHMAX        = 3; //�X�[�p�[�_�b�V���T�E���h�ԍ�
	const int JUMPEND        = 4; //���n�T�E���h�ԍ�
	const int DROP           = 5; //�q�b�v�h���b�v�T�E���h�ԍ�
	const int JUMP           = 6; //�W�����v�T�E���h�ԍ�
	const int DMM            = 7; //�X�[�p�[�_�b�V���ړ��T�E���h�ԍ�
	//8
	const int ENEMYDOWN      = 9; //�G�l�~�[�_�E���T�E���h�ԍ�
	const int ENEMYDOWN2     = 10;//�G�l�~�[�_�E��2�T�E���h�ԍ�
	const int ENEMYDOWNHIP   = 11;//�G�l�~�[�_�E���q�b�v�T�E���h�ԍ�
	const int BARDMOVE       = 12;//���T�E���h�ԍ�
	const int ENEMYMOVE      = 13;//�G�l�~�[�ړ��T�E���h�ԍ�
	const int ENEMYMOVE2     = 14;//�G�l�~�[�ړ�2�T�E���h�ԍ�
	const int FORTIDLE       = 15;//��C�ҋ@�T�E���h�ԍ�
	const int FORTSTAY       = 16;//��C���˃T�E���h�ԍ�
	const int FORTMOVE       = 17;//��C�ړ��T�E���h�ԍ�
	const int GAMEBGM        = 18;//�Q�[��BGM�T�E���h�ԍ�
	const int ENEMYJUMPCOUNT = 19;//�A�����݂��T�E���h�ԍ�
	const int TITLEA         = 20;//A�{�^�����̓T�E���h�ԍ�
	const int TITLEBGM       = 21;//�^�C�g��BGM�T�E���h�ԍ�
	const int BLOCK          = 22;//�u���b�N�j��T�E���h�ԍ�
	const int FALL           = 23;//�����T�E���h�ԍ�
};