#pragma once
using namespace std;

/// <summary>
/// �v���C���[�N���X
/// </summary>
namespace App {
	class EffectList;
	class SoundList;
	class Game;
	class FortTop;
	class Fort;
	class GoalPoint;
	class GameCamera;

	class Player :public IGameObject
	{
		//�v���C���[�̃X�e�[�g
		enum EnPlayerState {
			enPlayerState_Idle,       //�ҋ@
			enPlayerState_Idle2,      //���u���ҋ@
			enPlayerState_Walk,       //����
			enPlayerState_Dash,       //�_�b�V��
			enPlayerState_Dash_Max,   //�X�[�p�[�_�b�V��(�ő��_�b�V��)
			enPlayerState_Jump,       //�W�����v
			enPlayerState_Drop,       //�q�b�v�h���b�v
			enPlayerState_Fort_Ground,//��C�ړ�(�n��j
			enPlayerState_Fort_Air,   //��C�ړ�(�󒆁j
			enPlayerState_Goal,       //�S�[��(��]�j
			enPlayerState_Goal2,      //�S�[��(�_���X�j
			enPlayerState_Dead,       //���S
			enPlayerState_Fall        //����
		};
	public:
		Player();
		~Player();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
		//�ړ�����
		void Move();
		//�X�e�B�b�N����
		void Move_Stick();
		//�n��ړ�����
		void Move_Ground();
		//�󒆈ړ�����
		void Move_Air();
		//��C�ړ�����
		void Move_Fort();
		//�S�[���ړ�����
		void Move_Goal();
		//�ړ��X�e�[�g����
		void Move_Common();
		//HP����
		void HP();
		//�������ԏ���
		void TimeLimit();
		//��]����
		void Rotation();
		//�����蔻��
		void Collision();
		//�X�e�[�g����
		void ManageState();
		//�A�j���[�V��������
		void PlayAnimation();
		//�J�̃G�t�F�N�g
		void RainEffect();

		/// <summary>
		/// �ړ������̌v�Z�ɁA1�t���[���O�̈ړ��������g���@�\��L���ɂ���B
		/// </summary>
		void EnableUsingLastFrameMoveDirection()
		{
			m_usingLastFrameMoveDirection = true;
		}
		/// <summary>
		/// �ړ������̌v�Z�ɁA1�t���[���O�̈ړ��������g���@�\�𖳌��ɂ���B
		/// </summary>
		void DisableUsingLastFrameMoveDirection()
		{
			m_usingLastFrameMoveDirection = false;
		}
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="position">���W�B</param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// ���W���擾�B
		/// </summary>
		/// <returns>���W�B</returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rotation">��]�B</param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}
		/// <summary>
		/// ��]���擾�B
		/// </summary>
		/// <returns>��]�B</returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}
		/// <summary>
		/// �傫����ݒ�B
		/// </summary>
		/// <param name="scale">�傫���B</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// ���ݑ�W�����v���\�B
		/// </summary>
		/// <returns>�\�Ȃ�true�B</returns>
		bool JunpCount = false;
		/// <summary>
		/// ��C�ɏ�荞�ށB
		/// </summary>
		/// <returns>��C�ɏ�荞�ނȂ�true�B</returns>
		bool Fort_Idle = false;
		/// <summary>
		/// ��C�ړ��ŏ㏸����B
		/// </summary>
		/// <returns>��C�ړ��ŏ㏸����Ȃ�true�B</returns>
		bool Fort_Move = false;
		/// <summary>
		/// ��C�ړ��ŉ��~����B
		/// </summary>
		/// <returns>��C�ړ��ŉ��~����Ȃ�true�B</returns>
		bool Fort_Top = false;
		/// <summary>
		/// �v���C���[��`�悵�Ȃ��B
		/// </summary>
		/// <returns>�v���C���[��`�悵�Ȃ��Ȃ�true�B</returns>
		bool PlayerNotDraw = false;
		/// <summary>
		/// �S�[����Ԃł���B
		/// </summary>
		/// <returns>�S�[����Ԃł���Ȃ�true�B</returns>
		bool Goal = false;
		/// <summary>
		/// ���S��Ԃł���B
		/// </summary>
		/// <returns>���S��Ԃł���Ȃ�true�B</returns>
		bool Dead = false;
		/// <summary>
		/// ������Ԃł���B
		/// </summary>
		/// <returns>������Ԃł���Ȃ�true�B</returns>
		bool Fall = false;
		/// <summary>
		/// �ʏ�J������Ԃł���B
		/// </summary>
		/// <returns>�ʏ�J������Ԃł���Ȃ�true�B</returns>
		bool Default = true;
		/// <summary>
		/// ���s���J������Ԃł���B
		/// </summary>
		/// <returns>���s���J������Ԃł���Ȃ�true�B</returns>
		bool Forward = false;
		/// <summary>
		/// �W�����v���ł���B
		/// </summary>
		/// <returns>�W�����v��Ԃł���Ȃ�true�B</returns>
		bool PlayerJunp = false;
		/// <summary>
		/// �u���b�N�����ɏՓ˂��Ă���B
		/// </summary>
		/// <returns>�u���b�N�����ɏՓ˂��Ă���true�B</returns>
		bool Block_Hed = false;
		/// <summary>
		/// �G��A���œ��݂����1�����Z����B
		/// </summary>
		/// <returns>�A���œG�𓥂݂������B��x���n�����0�ɂ���B</returns>
		int Enemy_JunpCount = 0;
		/// <summary>
		/// UI�\���J�n���ԁB
		/// </summary>
		float m_UITime = 0.0f;
		/// <summary>
		/// �������ԁB(int�^�ɒ���)
		/// </summary>
		int Game_Timer = 0;
		/// <summary>
		/// �N���A��ʒm����B
		/// </summary>
		/// <returns>�N���A��ʒm����Ȃ�true�B</returns>
		bool Clear = false;

	private:
		//�����G�t�F�N�g�B
		void WalkEffect();
		//�_�b�V���G�t�F�N�g�B
		void DashEffect();
		//�X�[�p�[�_�b�V�����������̃G�t�F�N�g�B
		void Dash_MaxEffect();
		//�X�[�p�[�_�b�V���̉ΉԂ̃G�t�F�N�g�B
		void Dash_Max_FirstEffect();
		//�X�[�p�[�_�b�V���̉ΉԂ̏ł��Ղ̃G�t�F�N�g�B
		void Dash_Max_First2Effect();
		//�W�����v���̃G�t�F�N�g�B
		void JumpEffect();
		//�q�b�v�h���b�v���n�̃G�t�F�N�g�B
		void Drop_EndEffect();
		//�Q�[���N���A�̃G�t�F�N�g�B
		void ClearEffect();
		//���̍U������B
		void HedCollision();
		//���̍U������B
		void LegCollision();
		//���K�̍U������B
		void HipCollision();
		//���ʃX�e�[�g�̑J�ڏ����B
		void ProcessCommonStateTransition();
		//�W�����v�X�e�[�g�̑J�ڏ����B
		void ProcessJumpStateTransition();
		//�q�b�v�h���b�v�X�e�[�g�̑J�ڏ����B
		void ProcessDropStateTransition();
		//��C�ړ��X�e�[�g�̑J�ڏ����B
		void ProcessFortStateTransition();
		//�S�[��(��]�j�X�e�[�g�̑J�ڏ����B
		void ProcessGoalStateTransition();
		//�S�[��(�_���X�j�X�e�[�g�̑J�ڏ����B
		void ProcessGoal2StateTransition();
		//���S�X�e�[�g�̑J�ڏ����B
		void ProcessDeadStateTransition();
		//�A�j���[�V�����̓ǂݍ��݁B
		void InitAnimation();
		//�摜�̓ǂݍ��݁B
		void InitSprite();
		//�A�j���[�V�����C�x���g�p�̊֐��B
		void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

		//�v���C���[�̃A�j���[�V�����N���b�v�B
		enum EnAnimationClip {
			enAnimationClip_Idle,       //�ҋ@
			enAnimationClip_Idle2,      //���u���ҋ@
			enAnimationClip_Walk,       //����
			enAnimationClip_Dash,       //�_�b�V��
			enAnimationClip_Dash_Max,   //�X�[�p�[�_�b�V��(�ő��_�b�V��)
			enAnimationClip_Jump,       //�W�����v
			enAnimationClip_Drop,       //�q�b�v�h���b�v
			enAnimationClip_Fort_Ground,//��C�ړ�(�n��j
			enAnimationClip_Fort_Air,   //��C�ړ�(�󒆁j
			enAnimationClip_Goal,       //�S�[��(��]�j
			enAnimationClip_Goal2,      //�S�[��(�_���X)
			enAnimationClip_Dead,       //���S
			enAnimationClip_Fall,       //����
			enAnimationCilp_Num,
		};

		ModelRender         m_modelRender;                     //���f�������_�[
		Vector3             m_position;                        //���W
		Quaternion          m_rotation;                        //��]
		Vector3             m_forward = Vector3::AxisZ;        //���ʃx�N�g��
		Vector3             m_scale;                           //�傫��
		Vector3             m_moveSpeed;                       //�ړ����x
		Vector3             m_inertiaSpeed;                    //����
		Vector3				m_lastFrameLStick;				   //1�t���[���O��L�X�e�B�b�N�̓��͗�
		Vector3				m_lastFrameMoveDirection;		   //1�t���[���O�̈ړ�����
		bool				m_usingLastFrameMoveDirection;	   //1�t���[���O�̈ړ��������g���H
		EnPlayerState		m_playerState = enPlayerState_Idle;//�v���C���[�̃X�e�[�g

		EffectList* m_effectlist = nullptr;              //�G�t�F�N�g���X�g
		SoundList* m_soundlist = nullptr;             //�T�E���h���X�g
		CollisionObject* m_collisionObject;                 //�R���W�����I�u�W�F�N�g
		CharacterController m_charaCon;                        //�L�����N�^�[�R���g���[���[
		EffectEmitter* m_effectEmitter = nullptr;         //�G�t�F�N�g
		AnimationClip       m_animClips[enAnimationCilp_Num];  //�A�j���[�V�����N���b�v
		Game* m_game = nullptr;                  //�Q�[��
		Fort* m_fort = nullptr;                  //��C
		FortTop* m_fortTop = nullptr;               //��C�ړ��̒��_�|�C���g
		GoalPoint* m_goal = nullptr;                  //�S�[���|�C���g
		GameCamera* m_gameCamera = nullptr;            //�Q�[���J����

		SpriteRender		m_aiconSprite;  //�L�����N�^�[�A�C�R���摜
		SpriteRender        m_timerSprite;
		SpriteRender		m_clear;        //�N���A�摜
		wstring				m_hpCountwst;   //HP������
		wstring				m_timeLimittwst;//�������ԕ�����
		FontRender          m_hpCountFont;  //HP�t�H���g
		FontRender          m_timeLimitFont;//�������ԃt�H���g

		float               m_startTime = 0.0f;      //����J�n����
		float			    m_idleTime = 0.0f;       //�ҋ@���ԁB
		float               m_jumpTime = 0.0f;       //�W�����v�̃N�[���^�C��
		float               m_jumpInputTime = 0.0f;  //�W�����v�{�^���̓��͎���
		float               m_moveTime = 0.0f;       //MoveEffect�̍Đ��J�n����         
		float               m_dashTime = 0.0f;       //�_�b�V����������
		float               m_dropTime = 1.0f;       //�q�b�v�h���b�v�̒��n�d������
		float               m_fortTime = 0.0f;       //��C�ړ�(�n��)�o���鎞��

		/// <summary>
		/// �X�[�p�[�_�b�V�����������̃G�t�F�N�g���Đ�����B
		/// </summary>
		/// <returns>�G�t�F�N�g���Đ�����Ȃ�true�B</returns>
		bool Dash_Max_Effect = true;
		/// <summary>
		/// �X�[�p�[�_�b�V���̉ΉԁA�ł��Ղ̃G�t�F�N�g���Đ�����B
		/// </summary>
		/// <returns>�G�t�F�N�g���Đ�����Ȃ�true�B</returns>
		bool Dash_Max_Start_Effect = true;
		/// <summary>
		/// ���n�̃G�t�F�N�g���Đ�����B
		/// </summary>
		/// <returns>�G�t�F�N�g���Đ�����Ȃ�true�B</returns>
		bool Jump_End_Effect = false;
		/// <summary>
		/// �d�͂͒ʏ�̏�Ԃ��B
		/// </summary>
		/// <returns>�ʏ�̏�ԂȂ�true�B</returns>
		bool Gravity = true;
		/// <summary>
		/// �W�����v�͉\�ȏ�Ԃ��B
		/// </summary>
		/// <returns>�\�ȏ�ԂȂ�true�B</returns>
		bool SecondJump = true;
		/// <summary>
		/// �q�b�v�h���b�v�����B
		/// </summary>
		/// <returns>�q�b�v�h���b�v���Ȃ�true�B</returns>
		bool Drop = false;
		/// <summary>
		/// �q�b�v�h���b�v���������B
		/// </summary>
		/// <returns>�q�b�v�h���b�v�������Ȃ�true�B</returns>
		bool Stop = false;
		/// <summary>
		/// ��C�ړ����ʉ����Đ�����B
		/// </summary>
		/// <returns>��C�ړ����ʉ����Đ��o����Ȃ�true�B</returns>
		bool Fort_Move_Se = true;
		/// <summary>
		/// �S�[��(�_���X)���o���邩�B
		/// </summary>
		/// <returns>�S�[��(�_���X)���o����Ȃ�true�B</returns>
		bool Goal2 = false;
		/// <summary>
		/// �X�e�B�b�N�̑��삪����Ă��邩�B
		/// </summary>
		/// <returns>�X�e�B�b�N�̑��삪����Ă���Ȃ�true�B</returns>
		bool Stick = false;
		/// <summary>
		/// �G�l�~�[��A���œ��݂������̌��ʉ����Đ�����B
		/// </summary>
		/// <returns>�G�l�~�[��A���œ��݂������̌��ʉ����Đ�����Ȃ�true�B</returns>
		bool Enemy_JumpCountSE = true;
		/// <summary>
		/// �����̌��ʉ����Đ�����B
		/// </summary>
		/// <returns>�����̌��ʉ����Đ�����Ȃ�true�B</returns>
		bool Fall_SE = true;
		/// <summary>
		/// �v���C���[����]����n�ʂɏ���Ă��邩�B
		/// </summary>
		/// <returns>�v���C���[����]����n�ʂɏ���Ă���Ȃ�true�B</returns>
		bool OnGroundMove = false;
		/// <summary>
		/// �v���C���[���u���b�N�ɏ���Ă��邩�B
		/// </summary>
		/// <returns>�v���C���[���u���b�N�ɏ���Ă���Ȃ�true�B</returns>
		bool OnBlock = false;
		/// <summary>
		/// �v���C���[���u���b�N�ɉ�����Փ˂��Ă��邩�B
		/// </summary>
		/// <returns>�v���C���[���u���b�N�ɉ�����Փ˂Ȃ�true�B</returns>
		bool HitBlock = false;
		/// <summary>
		/// �����������\���B
		/// </summary>
		/// <returns>�����������\�Ȃ�true�B</returns>
		bool ReTry = true;
	};
}