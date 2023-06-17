#pragma once

/// <summary>
/// �Q�[���J�����N���X
/// </summary>
namespace App {
	class Player;
	class GoalPoint;
	class Game;
	class GameCamera :public IGameObject
	{
	public:
		GameCamera();
		~GameCamera();
		bool Start();
		void Update();
	private:
		//�ʏ�J�����ݒ�
		void DefaultUpdatePositionAndTarget();
		//�S�[���J�����ݒ�
		void GoalUpdatePositionAndTarget();
		//�ʏ�̃J�����A���O��
		void DefaultCamera();
		//���s����������J�����A���O��      
		void ForWardCamera();
		//��C���ˑO�̃J�����A���O��
		void FortStayCamera();
		//��C�ړ����㏸�̃J�����A���O��
		void FortMoveUpCamera();
		//��C�ړ����~���̃J�����A���O��
		void FortMoveFallCamera();
		//�S�[�����̃J�����A���O��
		void GoalCamera();
		//���S���̃J�����A���O��
		void DeadCamera();

		Vector3               m_toCameraPos = Vector3::One;//���W
		Quaternion            m_toCamerarot;               //��]
		Player* m_player;                    //�v���C���[                            
		GoalPoint* m_goal;                      //�S�[��
		Game* m_game;                      //�Q�[��
	};
}