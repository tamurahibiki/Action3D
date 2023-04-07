#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Game.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "CollisionObject.h"
#include "Fort.h"
#include "FortTop.h"
#include "GoalPoint.h"
#include "EffectList.h"
#include "SoundList.h"

namespace
{
	const float ZERO = 0.0f;//�[��
	//////////////////////////////////////
	////��������v���C���[�̏����ݒ�̒萔���`����B
	//////////////////////////////////////
	const Vector3 MODELSCALE = { 0.5f, 0.5f, 0.5f };          //���f���̑傫��
	const Vector3 TRYPOS     = { -2000.0f, 100.0f, 33000.0f };//���Ԓn�_���B��A���X�|�[�����W
	const float FIRSTADDITIONROTY = 80.0f; //�����ʒu�ŉ��Z�����]
	const float FALLDEAD          = 200.0f;//�������S���C��
	//////////////////////////////////////
	////�v���C���[�̏����ݒ�̒萔���`����̂͂����܂ŁB
	//////////////////////////////////////
	
	//////////////////////////////////////
	////��������v���C���[�̈ړ��̒萔���`����B
	//////////////////////////////////////
	const float GRAVITY                   = 30.0f;  //�ʏ펞�̏d��
	const float JUMPUPGRAVITY             = 18.0f;  //�W�����v�㏸���̏d��
	const float DROPGRAVITY               = 700.0f; //�q�b�v�h���b�v���̏d��
	const float FALLHEDGRAVITY            = 15.0f;  //���S���B�u���b�N�Փˎ��̏d��
	const float SJUMP                     = 10.0f;  //�������ŉ��Z����W�����v��
	const float FJUMP                     = 400.0f; //�ŏ��̃W�����v��
	const float NJUMP                     = 200.0f; //���݂���A�ǉ����͂��Ȃ������W�����v��
	const float MAXJUMPSPEED              = 1000.0f;//�ʏ�W�����v���̍ō����x
	const float MAXJUMPCOUNTSPEED         = 350.0f; //���ݑ�W�����v���̍ō����x
	const float WALK                      = 200.0f; //�������x
	const float DASH                      = 300.0f; //�_�b�V�����x
	const float MAXDASH                   = 350.0f; //�X�[�p�[�_�b�V�����x
	const float INERTIAMULTIPLICATION     = 0.95f;  //�����ړ����A��Z���鑬�x
	const float FORTINERTIAMULTIPLICATION = 0.2f;   //��C�����ړ����A��Z���鑬�x
	const float FORTGROUNDMULTIPLICATION  = 0.4f;   //��C�ړ�(�n��)���A��Z����鑬�x
	const float GOALMULTIPLICATION        = 20.0f;  //�S�[�����A��Z����鑬�x
	const float ONGROUNDMOVE              = 150.0f; //��]����n�ʂɏ���Ă��鎞�ɉ��Z����鑬�x
	const float FORTIDLE                  = 55.0f;  //��C���ˑO���x
	const float FORTMOVE                  = 670.0f; //��C���ˌ㑬�x
	//////////////////////////////////////
	////�v���C���[�̈ړ��̒萔���`����̂͂����܂ŁB
	//////////////////////////////////////
	
	//////////////////////////////////////
	////��������v���C���[�̓����蔻��̒萔���`����B
	//////////////////////////////////////
	const float CHARACONRADIUSGROUND = 90.0f; //�n�㎞�̃L�����N�^�[�R���g���[���[�̔��a
	const float CHARACONHEIGHTGROUND = 80.0f; //�n�㎞�̃L�����N�^�[�R���g���[���[�̍���
	const float CHARACONHITBLOCK     = 60.0f; //�u���b�N�Փˎ��̃L�����N�^�[�R���g���[���[�̔��a�A����
	const float BODYCOLLISIONSCALE   = 140.0f;//Body�R���W�����̑傫��
	const float HEDCOLLISIONPOSY     = 500.0f;//���̃R���W�����̍���
	const float LEGCOLLISIONPOSY     = 100.0f;//���̃R���W�����̍���
	const float HIPCOLLISIONPOSY     = 150.0f;//���K�̃R���W�����̍���
	const Vector3 HEDCOLLISIONSCALE  = { 120.0f, 200.0f, 120.0f };//���̃R���W�����̑傫��
	const Vector3 LEGCOLLISIONSCALE  = { 50.0f, 50.0f, 50.0f };   //���̃R���W�����̑傫��
	const Vector3 HIPCOLLISIONSCALE  = { 150.0f, 150.0f, 150.0f };//���K�̃R���W�����̑傫��
	//////////////////////////////////////
	////�v���C���[�̓����蔻��̒萔���`����̂͂����܂ŁB
	//////////////////////////////////////

	//////////////////////////////////////
	////��������Q�[���p�b�h�̍��X�e�B�b�N�̒萔���`����B
	//////////////////////////////////////
	const float BLOCKHEDSTICK     = 0.1f;//�u���b�N�����ɏՓ˂������ɏ�Z���鍶�X�e�B�b�N���͗�
	const float AIRSTICK          = 0.7f;//�󒆂ɂ��鎞�ɏ�Z���鍶�X�e�B�b�N���͗�
	const float LASTFRAMESTICKDOT = 0.9f;//���X�e�B�b�N�̓��͗ʂ̓���
	//////////////////////////////////////
	////�Q�[���p�b�h�̍��X�e�B�b�N�̒萔���`����̂͂����܂ŁB
	//////////////////////////////////////

	//////////////////////////////////////
	////��������Q�[���J�����̒萔���`����B
	//////////////////////////////////////
	const float   CAMERAFAR = 320000.0f;                 //�����ʂ܂ł̋���
	const Vector3 CAMERAPOS = { 0.0f, 1000.0f,-1000.0f };//�J�����̍��W
	//////////////////////////////////////
	////�Q�[���J�����̒萔���`����̂͂����܂ŁB
	//////////////////////////////////////
	
	//////////////////////////////////////
	////��������^�C�}�[�̒萔���`����B
	//////////////////////////////////////
	const float SPAWNTIME         = 1.0f;//�X�|�[������̏��������鎞��
	const float UITIMEMAX         = 2.0f;//UI�̕\�����J�n���鎞��
	const float STARTTIMEMAX      = 1.9f;//�v���C���[�̑��삪�J�n�ł��鎞��
	const float IDLETIMEMAX       = 6.0f;//���u���ҋ@�X�e�[�g�ɂ��鎞��
	const float DASHTIMEMAX       = 2.0f;//�X�[�p�[�_�b�V���ɂȂ鎞��
	const float DROPTIMEMAX       = 0.5f;//�q�b�v�h���b�v�̒��n�d�����I�����鎞��
	const float JUMPTIMEMAX       = 0.2f;//�W�����v�̃N�[���^�C�����I�����鎞��
	const float JUMPINPUTTIMEMAX  = 0.6f;//�W�����v�{�^�����͎�t����
	const float FORTTIMEMAX       = 0.4f;//��C�ړ�(�n��)����
	const float MOVEEFFECTTIMEMAX = 0.3f;//�G�t�F�N�g���Đ��J�n����
	//////////////////////////////////////
	////�^�C�}�[�̒萔���`����̂͂����܂ŁB
	//////////////////////////////////////
	
	//////////////////////////////////////
	////��������G�t�F�N�g�̒萔���`����B
	//////////////////////////////////////
	const Vector3 WALKDASHEFFECTSCALE = { 50.0f,50.0f,50.0f };   //�����A�_�b�V���̃G�t�F�N�g�̑傫��
	const Vector3 DMFEFFECTSCALE      = { 60.0f,50.0f,50.0f };   //�ΉԂ̃G�t�F�N�g�̑傫��
	const Vector3 DMF2EFFECTSCALE     = { 30.0f,30.0f,30.0f };   //�ł��Ղ̃G�t�F�N�g�̑傫��
	const Vector3 JUMPEFFECTSCALE     = { 40.0f,20.0f,40.0f };   //�W�����v�̃G�t�F�N�g�̑傫��
	const Vector3 DROPEFFECTSCALE     = { 50.0f,60.0f,50.0f };   //�q�b�v�h���b�v�̃G�t�F�N�g�̑傫��
	const Vector3 CLEAREFFECTSCALE    = { 100.0f,100.0f,100.0f };//�N���A�̃G�t�F�N�g�̑傫��
	//////////////////////////////////////
	////�G�t�F�N�g�̒萔���`�̂͂����܂ŁB
	//////////////////////////////////////
	
	//////////////////////////////////////
	////��������摜�̒萔���`����B
	//////////////////////////////////////
	const Vector2 ATCSPRITEPIVOT = { 0.0f, 0.5f };           //�A�C�R���A�������ԁA�N���A�摜�̃s�{�b�g
	const Vector3 AICONSPRITEPOS = { -800.0f, 370.0f, 0.0f };//�A�C�R���摜�̍��W
	const Vector3 TIMERSPRITEPOS = { 550.0f, 385.0f, 0.0f }; //�������ԉ摜�̍��W
	const Vector3 CLEARSPRITEPOS = { -400.0f, 100.0f, 0.0f };//�N���A�摜�̍��W
	//////////////////////////////////////
	////�摜�̒萔���`����̂͂����܂ŁB
	//////////////////////////////////////

	//////////////////////////////////////
	////��������t�H���g�֌W�̒萔���`����B
	//////////////////////////////////////
	/// <summary>
	/// HP(�c�@)
	/// </summary>
	const Vector2 HPFONTPIVOT       = { 1.0f,1.0f };          //HP�t�H���g�̃s�{�b�g
	const Vector3 HPFONTPOS         = { -785.0f,460.0f,0.0f };//HP�t�H���g�̍��W
	const float   HPFONTSCALE       = 1.3f;                   //HP�t�H���g�̑傫��
	const float   HPFONTOFFSET      = 3.0f;                   //HP�t�H���g�̃I�t�Z�b�g��
	const int     HPFONTCOLORRED    = 1;                      //�ԐF�ɂ���c��HP
	const int     HPFONTCOLORYELLOW = 3;                      //���F�ɂ���c��HP
	/// <summary>
	/// ��������
	/// </summary>
	const Vector2 TIMEFONTPIVOT       = { 0.0f,0.0f };         //�������ԃt�H���g�̃s�{�b�g
	const Vector3 TIMEFONTPOS         = { 760.0f,550.0f,0.0f };//�������ԃt�H���g�̍��W
	const float   TIMEFONTSCALE       = 2.0f;                  //�������ԃt�H���g�̑傫��
	const float   TIMEFONTOFFSET      = 3.0f;                  //�������ԃt�H���g�̃I�t�Z�b�g��
	const int     TIMEFONTCOLORRED    = 30;                    //�ԐF�ɂ���c�萧������
	const int     TIMEFONTCOLORYELLOW = 100;                   //���F�ɂ���c�萧������
	//////////////////////////////////////
	////�t�H���g�֌W�̒萔���`����̂͂����܂ŁB
	//////////////////////////////////////
}

Player::Player(){}
Player::~Player() 
{
	//�Q�[���J�������폜����B
	DeleteGO(m_gameCamera);
}
bool Player::Start()
{
	//�摜��ǂݍ��ށB
	InitSprite();
	m_game = FindGO<Game>("game");
	//�A�j���[�V������ǂݍ��ށB
	InitAnimation();
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/player/Player.tkm", false, m_animClips, enAnimationCilp_Num);
	//���Ԓn�_�ɓ��B���Ă���Ȃ�
	if (m_game->Try == true)
	{
		//�X�|�[���n�_��ς���
		m_position = TRYPOS;
		//��]��ݒ肷��B
		m_modelRender.SetRotation(m_rotation);
	}
	else
	{
		//���W��ݒ肷��B
		m_modelRender.SetPosition(m_position);
		//��]��ݒ肷��B
		m_modelRender.SetRotation(m_rotation);
		m_rotation.SetRotationY(FIRSTADDITIONROTY);
	}
	//�傫����ݒ肷��B
	m_modelRender.SetScale(MODELSCALE);
	//���f�����X�V����B
	m_modelRender.Update();
	//�����蔻����쐬����B
	m_charaCon.Init(
		CHARACONRADIUSGROUND,//���a
		CHARACONHEIGHTGROUND,//����
		m_position//���W
	);
	//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});
	//�v���C���[�����܂ꂽ����Ȃ�
	if (m_game->PlayerSpawn == true)
	{
		//�J�n���Ԃ�1.0�b����X�^�[�g����B
		m_startTime = SPAWNTIME;
		m_UITime = SPAWNTIME;
		m_game->PlayerSpawn = false;
	}

	//�Q�[���J�����̍��W��ݒ肷��B
	g_camera3D->SetPosition(CAMERAPOS);
	//�����ʂ�ݒ肷��B
	g_camera3D->SetFar(CAMERAFAR);
	//�Q�[���J�����I�u�W�F�N�g���쐬����B
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	
	m_effectlist = FindGO<EffectList>("effectlist");
	m_soundlist = FindGO<SoundList>("soundlist");
	
	m_fort    = FindGO<Fort>("fort");
	m_fortTop = FindGO<FortTop>("forttop");
	m_goal    = FindGO<GoalPoint>("goalpoint");
	return true;
}
void Player::Update()
{
	//�������Ԃ�0�b�ɂȂ�����
	if (m_game->m_gameTime <= ZERO)
	{
		//�v���C���[���S��̏����ɑJ�ڂ���B
		m_game->Retry();
		return;
	}
	//UI�\���J�n�^�C�}�[��2.0�b�ȉ��Ȃ�
	if (m_UITime < UITIMEMAX)
	{
		//UI�\���J�n�^�C�}�[�����Z����B
		m_UITime += g_gameTime->GetFrameDeltaTime();
	}
	//����J�n�^�C�}�[��1.9�b�ȉ��Ȃ�
	if (m_startTime < STARTTIMEMAX)
	{
		//����J�n�^�C�}�[�����Z����B
		m_startTime += g_gameTime->GetFrameDeltaTime();
		return;
	}
	//HP�̏����B
	HP();
	//�������Ԃ̏����B
	TimeLimit();
	//���X�e�B�b�N�����삳��Ă�����
	if (g_pad[0]->GetLStickXF() && g_pad[0]->GetLStickYF())
	{
		//���X�e�B�b�N�����삳��Ă���B
		Stick = true;
	}
	//���X�e�B�b�N�����삳��Ă��Ȃ��Ȃ�
	else if (!g_pad[0]->GetLStickXF() && !g_pad[0]->GetLStickYF())
	{
		//���X�e�B�b�N�����삳��Ă��Ȃ��B
		Stick = false;
	}
	//�������S���C���𒴂��Ă�����
	if (m_position.y < -FALLDEAD)
	{
		//�����̌��ʉ���1�x��������B
		if (Fall_SE == true)
		{
			//���ʉ���ݒ肷��B
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(23);
			se->Play(false);//���[�v�Đ����Ȃ��B
			se->SetVolume(0.2f);//�{�����[���̐ݒ�B
			Fall_SE = false;
		}
		//���S��Ԃɂ���B
		Dead = true;
		//������Ԃɂ���B
		Fall = true;
		//�����X�e�[�g�ɑJ�ڂ���B
		m_playerState = enPlayerState_Fall;
	}
	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//�R���W�����̍��W��ݒ肷��B
	Vector3 m_bodyposition = m_position;
	m_bodyposition.y = m_position.y + 200.0f;
	//���`��̃R���W�������쐬����B
	m_collisionObject->CreateSphere(
		m_bodyposition, //���W
		Quaternion::Identity, //��]
		BODYCOLLISIONSCALE//�傫��
	);
	////���O��Body�ɂ���B
	m_collisionObject->SetName("Body");
	
	//�ړ������B
	Move();
	//��]�����B
	Rotation();
	//�����蔻��B
	Collision();
	//�X�e�[�g�̑J�ڏ����B
	ManageState();
	//�A�j���[�V�����̍Đ��B
	PlayAnimation();
	//���f���̍X�V�B
	m_modelRender.Update();
}
void Player::Move()
{
	//�����X�e�[�g���u���b�N�ɓ����Փ˂��Ă�����
	if (m_playerState == enPlayerState_Fall || Block_Hed == true)
	{
		//�����X�e�[�g�Ȃ�
		if (m_playerState == enPlayerState_Fall)
		{
			//x.z�����̈ړ����x��0�ɂ���B
			m_moveSpeed.x = ZERO;
			m_moveSpeed.z = ZERO;
		}
		//�d�͂𔼕��ɂ���B
		m_moveSpeed.y -= FALLHEDGRAVITY;
	}
	//���S�X�e�[�g�Ȃ�
	if (m_playerState==enPlayerState_Dead)
	{
		//���������͏������Ȃ��B
		return;
	}
	//�S�[�����̏����B
	Move_Goal();
	//��C���̏����B
	Move_Fort();
	//��C�ړ��A�S�[���A���S�A����������Ă��Ȃ��Ȃ�
	if (Fort_Idle == false && Fort_Move == false
		&& Fort_Top == false && Goal == false && Goal2 == false && Fall == false)
	{ 
		//�X�e�B�b�N�̓��͗ʏ����B
		Move_Stick();
		//�n��ړ������B
		Move_Ground();
		//�󒆈ړ������B
		Move_Air();
	}
	//�A���œ��݂�����2�Ȃ�
	if (Enemy_JunpCount == 2)
	{
		//���ʉ����Đ�����B
		if (Enemy_JumpCountSE == true)
		{
			/*m_bgm = NewGO<SoundSource>(0);
			m_bgm->Init(19);
			m_bgm->Play(false);
			m_bgm->SetVolume(0.5f);
			Enemy_JumpCountSE = false;*/
		}
	}
	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = m_charaCon.Execute(m_moveSpeed, 5.0f / 60.0f);
	m_lastFrameMoveDirection = m_moveSpeed;
	m_lastFrameMoveDirection.Normalize();
	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);	
}
void Player::Move_Stick()
{
	//x.z�����̈ړ����x��0�ɂ���B
	m_moveSpeed.x = ZERO;
	m_moveSpeed.z = ZERO;
	Vector3 stickL;
	//�n��ɂ���Ȃ�
	if (m_charaCon.IsOnGround())
	{
		//���X�e�B�b�N�̓��͗ʂ����̂܂ܓn���B
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();
	}
	//�q�b�v�h���b�v���Ȃ�
	else if (Stop == true || Drop == true)
	{
		//���X�e�B�b�N�̓��͗ʂ�0�ɂ���B
		stickL.x = g_pad[0]->GetLStickXF() * ZERO;
		stickL.y = g_pad[0]->GetLStickYF() * ZERO;
	}
	//�u���b�N�����ɏՓ˂��Ă���Ȃ�
	else if (Block_Hed == true)
	{
		//���X�e�B�b�N�̓��͗ʂ�0.1�{�ɂ���B
		stickL.x = g_pad[0]->GetLStickXF() * BLOCKHEDSTICK;
		stickL.y = g_pad[0]->GetLStickYF() * BLOCKHEDSTICK;
	}
	//�󒆂�
	else
	{
		//�u���b�N�ɏՓ˂��Ă��Ȃ��Ȃ�
		if (HitBlock == false)
		{
			//���X�e�B�b�N�̓��͗ʂ�0.7�{�ɂ���B
			stickL.x = g_pad[0]->GetLStickXF() * AIRSTICK;
			stickL.y = g_pad[0]->GetLStickYF() * AIRSTICK;
		}
		//�u���b�N�ɏՓ˂��Ă���Ȃ�
		else
		{
			//���X�e�B�b�N�̓��͗ʂ�0�ɂ���B
			stickL.x = g_pad[0]->GetLStickXF() * ZERO;
			stickL.y = g_pad[0]->GetLStickYF() * ZERO;
		}
	}
	//�J�����̑O�����̃x�N�g���������Ă���B
	Vector3 forward;
	//�J�����̉E�����̃x�N�g���������Ă���B
	Vector3 right;
	//�J�����̑O�����������Ă���B
	forward = g_camera3D->GetForward();
	//�J�����̉E�����������Ă���B
	right = g_camera3D->GetRight();
	//y�����̃x�N�g����0�ɂ���B
	forward.y = ZERO;
	right.y = ZERO;
	//X��Y�{�^���������Ă��āA�_�b�V���������Ԃ�2�b�ȉ��Ȃ�
	if (g_pad[0]->IsPress(enButtonX) && m_dashTime < DASHTIMEMAX
		|| g_pad[0]->IsPress(enButtonY) && m_dashTime < DASHTIMEMAX)
	{
		//�_�b�V���������Ԃ����Z����B
		m_dashTime += g_gameTime->GetFrameDeltaTime();
		//���X�e�B�b�N�̓��͗ʂɃ_�b�V�����x����Z����B
		right *= stickL.x * DASH;
		forward *= stickL.y * DASH;
	}
	//X��Y�{�^���������Ă��āA�_�b�V���������Ԃ�2�b�ȏ�Ȃ�
	else if (g_pad[0]->IsPress(enButtonX) && m_dashTime > DASHTIMEMAX
		|| g_pad[0]->IsPress(enButtonY) && m_dashTime > DASHTIMEMAX)
	{
		//���X�e�B�b�N�̓��͗ʂɃX�[�p�[�_�b�V�����x����Z����B
		right *= stickL.x * MAXDASH;
		forward *= stickL.y * MAXDASH;
	}
	//X��Y�{�^���������Ă��Ȃ��Ȃ�
	else
	{
		//�_�b�V���������Ԃ�0�ɂ���B
		m_dashTime = ZERO;
		//���X�e�B�b�N�̓��͗ʂɕ������x����Z����B
		right *= stickL.x * WALK;
		forward *= stickL.y * WALK;
	}
	//���X�e�B�b�N�����삳��Ă���Ȃ�
	if (Stick == true)
	{
		//1�t���[���O�̈ړ��������g���Ȃ�
		if (m_usingLastFrameMoveDirection) {
			//���X�e�B�b�N�̓��͗ʂ̓��ς�0.9�ȉ��ɂȂ�����
			if (m_lastFrameLStick.Dot(stickL) < LASTFRAMESTICKDOT) {
				//1�t���[���O�̈ړ��������g��Ȃ��B
				m_usingLastFrameMoveDirection = false;
			}
			//1�t���[���O�̈ړ��������g����������B
			m_moveSpeed += m_lastFrameMoveDirection * (right + forward).Length();
		}
		//1�t���[���O�̈ړ��������g��Ȃ��Ȃ�
		else {
			//1�t���[���O�̈ړ������Ɍ��݂̍��X�e�B�b�N�̓��͗ʂ�n���Ă����B
			m_lastFrameLStick.x = stickL.x;
			m_lastFrameLStick.y = stickL.y;
			//�ړ����x���v�Z����B
			m_moveSpeed += right + forward;
		}
		//�������x�Ɍ��݂̈ړ����x��n���Ă����B
		m_inertiaSpeed = m_moveSpeed;
	}
	//���X�e�B�b�N�����삳��Ă��Ȃ��Ȃ�
	else if (Stick == false)
	{
		//1�t���[���O�̈ړ��������g��Ȃ��B
		m_usingLastFrameMoveDirection = false;
		//�_�b�V���������Ԃ�0�ɂ���B
		m_dashTime = ZERO;
		//�u���b�N�̏�ɂ��Ȃ��Ȃ�
		if (OnBlock == false)
		{
			//�������x��0.95f����Z����B
			m_inertiaSpeed *= INERTIAMULTIPLICATION;
		}
		//y�����̈ړ����x��0�ɂ���B
		m_inertiaSpeed.y = ZERO;
		//���݂̈ړ����x�Ɋ������x��n���Ă����B
		m_moveSpeed += m_inertiaSpeed;
	}
}
void Player::Move_Ground()
{
	//�n�ʂɕt���Ă��邩�A�u���b�N�̏�ɂ�����B
	if (m_charaCon.IsOnGround() || OnBlock == true)
	{
		//�����蔻����폜����B
		m_charaCon.RemoveRigidBoby();
		//�����蔻����쐬����B
		m_charaCon.Init(
			CHARACONRADIUSGROUND,//���a
			CHARACONHEIGHTGROUND,//����
			m_position//���W
		);
		//�u���b�N�����ɏՓ˂��Ă��Ȃ��B
		Block_Hed = false;
		//�u���b�N���̂ɏՓ˂��Ă��Ȃ��B
		HitBlock = false;
		//�A�����݂�����0�ɂ���B
		Enemy_JunpCount = ZERO;
		//�A�����݂��̌��ʉ����Đ��ł���悤�ɂ���B
		Enemy_JumpCountSE = true;
		//�W�����v���̏��������Ȃ��B
		PlayerJunp = false;
		//�d�͂𖳂����B
		m_moveSpeed.y = ZERO;
		//�W�����v�{�^���̓��͎��Ԃ�0�ɂ���B
		m_jumpInputTime = ZERO;
		//�W�����v���\�ȏ�Ԃɂ���B
		SecondJump = true;
		//�v���C���[����]����n�ʂɏ���Ă�����
		if (OnGroundMove==true)
		{
			//-Z�����̈ړ����x�𑝂₷�A�܂���z�����̈ړ����x�����炷�B
			m_moveSpeed.z -= ONGROUNDMOVE;
		}
		//�q�b�v�h���b�v�̒��n�d�����Ԃ��I����Ă��Ȃ�������
		if (m_dropTime <= DROPTIMEMAX)
		{
			//�q�b�v�h���b�v�̒��n�d�����Ԃ��o�߂����Ă����B
			m_dropTime += g_gameTime->GetFrameDeltaTime();
			//x.z�����̈ړ����x��0�ɂ���B
			m_moveSpeed.x = ZERO;
			m_moveSpeed.z = ZERO;
			//���n�G�t�F�N�g���Đ��ł���Ȃ�
			if (Jump_End_Effect == true)
			{
				//�q�b�v�h���b�v�̒��n�G�t�F�N�g���Đ�����B
				Drop_EndEffect();
				Jump_End_Effect = false;
				//���ʉ���ݒ肷��B
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(m_soundlist->DROP);
				//���[�v�Đ����Ȃ��B
				se->Play(false);
				//�{�����[���̐ݒ�B
				se->SetVolume(0.3f);
			}
			return;
		}
		//�W�����v�̃N�[���^�C�����o�߂����Ă����B
		m_jumpTime += g_gameTime->GetFrameDeltaTime();
		//�W�����v�̃N�[���^�C�����I����Ă���Ȃ�
		if (m_jumpTime >= JUMPTIMEMAX)
		{
			//A��B�{�^���������Ă���Ȃ�
			if (g_pad[0]->IsPress(enButtonA) || g_pad[0]->IsPress(enButtonB))
			{
				//�W�����v�X�e�[�g�ɑJ�ڂ���B
				m_playerState = enPlayerState_Jump;
				//�W�����v������B
				m_moveSpeed.y += FJUMP;
				//���ʉ���ݒ肷��B
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(m_soundlist->JUMP);
				//���[�v�Đ����Ȃ��B
				se->Play(false);
				//�{�����[���̐ݒ�B
				se->SetVolume(0.2f);
				//�W�����v���ɂ���B
				PlayerJunp = true;
			}
		}
	}
}
void Player::Move_Air()
{
	//�󒆂ɂ���Ȃ�
	if (!m_charaCon.IsOnGround() && OnBlock == false)
	{
		//���n�G�t�F�N�g���Đ��ł���悤�ɂ���B�B
		Jump_End_Effect = true;
		//�ړ��G�t�F�N�g�̍Đ��J�n���Ԃ�0�ɂ���B
		m_moveTime = ZERO;
		//�W�����v�̃N�[���^�C��������������B
		m_jumpTime = ZERO;
		//�q�b�v�h���b�v(�~����)�Ȃ�
		if (Drop == true)
		{
			//���K�̍U��������쐬����B
			HipCollision();
		}
		//�q�b�v�h���b�v(�~����)�łȂ��Ȃ�
		if (Drop == false)
		{
			//�q�b�v�h���b�v(�~���O)�Ȃ�
			if (Stop == true)
			{
				//�d�͂��Ȃ����B
				m_moveSpeed.y = ZERO;
			}
			////�q�b�v�h���b�v(�~���O)�łȂ��Ȃ�
			else if (Stop == false)
			{
				//���̍U��������쐬����B
				LegCollision();
				//�ʏ�̏d�͂Ȃ�
				if (Gravity == true)
				{
					//�d�͂𔭐�������B
					m_moveSpeed.y -= GRAVITY;
				}
				//�W�����v�㏸���̏d�͂Ȃ�
				else if (Gravity == false)
				{
					//�d�͂𔭐�������B
					m_moveSpeed.y -= JUMPUPGRAVITY;
					//���̍U��������쐬����B
					HedCollision();
				}
			}
		}
		//�W�����v���\�ȏ�ԂȂ�
		if (SecondJump == true)
		{
			//A��B�{�^���������Ă��āA���͎��Ԃ�0.6�b�ȉ��Ȃ�
			if (g_pad[0]->IsPress(enButtonA) && m_jumpInputTime < JUMPINPUTTIMEMAX
				|| g_pad[0]->IsPress(enButtonB) && m_jumpInputTime < JUMPINPUTTIMEMAX)
			{
				//�W�����v�{�^���̓��͎��Ԃ����Z����B
				m_jumpInputTime += g_gameTime->GetFrameDeltaTime();

				//Y�����̈ړ����x��1000.0f�ȉ��Ȃ�
				if (m_moveSpeed.y <= MAXJUMPSPEED)
				{
					//�W�����v�͂����Z����B
					m_moveSpeed.y += SJUMP;
				}
				//Y�����̈ړ����x��1000.0f�ȏ�Ȃ�
				else
				{
					//Y�����̈ړ����x��1000.0f�ɂ���B
					m_moveSpeed.y = MAXJUMPSPEED;
				}
			}
			//�W�����v�{�^���̓��͎��Ԃ�0.6�b�ȏ�Ȃ�
			else
			{
				//�W�����v���s�\�ȏ�Ԃɂ���B
				SecondJump = false;
			}
		}
		//LB2��RB2�{�^���������Ă���Ȃ�
		if (g_pad[0]->IsTrigger(enButtonLB2) || g_pad[0]->IsTrigger(enButtonRB2))
		{
			//�q�b�v�h���b�v�X�e�[�g�ɑJ�ڂ���B
			m_playerState = enPlayerState_Drop;
			//�q�b�v�h���b�v�̒��n�d�����Ԃ�����������B
			m_dropTime = ZERO;
			//�q�b�v�h���b�v�̒��n�d�����Ԃ����Z����B
			m_dropTime += g_gameTime->GetFrameDeltaTime();
		}
		//���ݑ�W�����v���\�Ȃ�
		if (JunpCount == true)
		{
			//Y�����̈ړ����x��0�ɂ���B
			m_moveSpeed.y = ZERO;
			//���ݑ�W�����v��s�\�ɂ���B
			JunpCount = false;
			//A��B�{�^���������Ă���Ȃ�
			if (g_pad[0]->IsPress(enButtonA) || g_pad[0]->IsPress(enButtonB))
			{
				//Y�����̈ړ����x��350.0f�ȉ��Ȃ�
				if (m_moveSpeed.y <= MAXJUMPCOUNTSPEED)
				{
					//�W�����v�͂����Z����B
					m_moveSpeed.y += FJUMP;
				}
				//Y�����̈ړ����x��350.0f�ȏ�Ȃ�
				else
				{
					//Y�����̈ړ����x��350.0f�ɂ���B
					m_moveSpeed.y = MAXJUMPCOUNTSPEED;
				}
			}
			//A��B�{�^���������Ă��Ȃ��Ȃ�
			else
			{
				//Y�����̈ړ����x��350.0f�ȉ��Ȃ�
				if (m_moveSpeed.y <= MAXJUMPCOUNTSPEED)
				{
					//�Ⴂ�W�����v�͂����Z����B
					m_moveSpeed.y += NJUMP;
				}
				//Y�����̈ړ����x��350.0f�ȏ�Ȃ�
				else
				{
					//Y�����̈ړ����x��350.0f�ɂ���B
					m_moveSpeed.y = MAXJUMPCOUNTSPEED;
				}
			}
			//�W�����v�X�e�[�g�ɑJ�ڂ���B
			m_playerState = enPlayerState_Jump;
		}
	}
}
void Player::Move_Fort()
{
	//��C�ɏ�荞�ނȂ�
	if (Fort_Idle == true)
	{
		//��C����v���C���[�Ɍ������x�N�g�����v�Z����B
		Vector3 diff = m_fort->GetPosition() - m_position;
		//�v���C���[�����C�Ɍ������x�N�g���𐳋K������B
		diff.Normalize();
		//�ړ����x���v�Z����
		m_moveSpeed = diff * FORTIDLE;
		//��C�ړ�(��)�X�e�[�g�ɑJ�ڂ���B
		m_playerState = enPlayerState_Fort_Air;
	}
	//��C�ړ��ŏ㏸���Ă���Ȃ�
	if (Fort_Move == true)
	{
		//��C�ړ�(��)�X�e�[�g�ɑJ�ڂ���B
		m_playerState = enPlayerState_Fort_Air;
		//��C�ړ��̒��_�|�C���g����v���C���[�Ɍ������x�N�g�����v�Z����B
		Vector3 diff = m_fortTop->GetPosition() - m_position;
		//�v���C���[�����C�ړ��̒��_�|�C���g�Ɍ������x�N�g���𐳋K������B
		diff.Normalize();
		//�ړ����x���v�Z����B
		m_moveSpeed = diff * FORTMOVE;
		//���݂̈ړ����x���������x�ɓn���Ă����B
		m_inertiaSpeed = m_moveSpeed;
		//�G�t�F�N�g���Đ�����B
		DashEffect();
		//���ʉ�����x�����Đ�����B
		if (Fort_Move_Se == true)
		{
			//���ʉ���ݒ肷��B
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->FORTMOVE);
			//���[�v�Đ����Ȃ��B
			se->Play(false);
			//�{�����[���̐ݒ�B
			se->SetVolume(0.15f);
			Fort_Move_Se = false;
		}
	}
	//��C�ړ��ŉ��~���Ă���Ȃ�
	else if (Fort_Move == false && Fort_Top == true)
	{
		//��C�ړ�(��)�X�e�[�g�ɑJ�ڂ���B
		m_playerState = enPlayerState_Fort_Air;
		//�������x��0.2f����Z����B
		m_inertiaSpeed *= FORTINERTIAMULTIPLICATION;
		//�d�͂�������B
		m_inertiaSpeed.y -= GRAVITY;
		//�������x�����݂̈ړ����x�ɓn���B
		m_moveSpeed += m_inertiaSpeed;
		//�G�t�F�N�g���Đ�����B
		DashEffect();
		//�v���C���[�����n���Ă���Ȃ�
		if (m_charaCon.IsOnGround())
		{
			//��C�ړ�(�n��)�X�e�[�g�ɑJ�ڂ���B
			m_playerState = enPlayerState_Fort_Ground;
			//�ړ����x���v�Z����B
			m_moveSpeed += m_forward * FORTGROUNDMULTIPLICATION;
			//��C�ړ�(�n��)�o���鎞�Ԃ����Z����B
			m_fortTime += g_gameTime->GetFrameDeltaTime();
			////��C�ړ�(�n��)�o���鎞�Ԃ�0.4�b�ȏ�Ȃ�
			if (m_fortTime >= FORTTIMEMAX)
			{
				//��C�ړ��ō~�����鏈�������Ȃ��B
				Fort_Top = false;
				//��C�ړ�(�n��)�o���鎞�Ԃ����������Ă����B
				m_fortTime = ZERO;
			}
			//�ʏ�J������Ԃɂ���B
			Default = true;
			//���Ԓn�_�ɓ��B����B
			m_game->Try = true;
		}
	}
}
void Player::Move_Goal()
{
	//�S�[��(�_���X)���o����Ȃ�
	if (Goal2 == true)
	{
		//x.z�����̈ړ����x��0�ɂ���B
		m_moveSpeed.x = ZERO;
		m_moveSpeed.z = ZERO;
		//�S�[��(�_���X)�X�e�[�g�ɑJ�ڂ���B
		m_playerState = enPlayerState_Goal2;
		return;
	}
	//���n���Ă���
	if (m_charaCon.IsOnGround())
	{
		//�S�[����ԂȂ�
		if (Goal == true)
		{
			//x.z�����̈ړ����x��0�ɂ���B
			m_moveSpeed.x = ZERO;
			m_moveSpeed.z = ZERO;
			//�S�[���|�C���g����v���C���[�Ɍ������x�N�g�����v�Z����B
			Vector3 diff = m_goal->GetPosition() - m_position;
			//�v���C���[����S�[���|�C���g�Ɍ������x�N�g���𐳋K������B
			diff.Normalize();
			//�ړ����x���v�Z����B
			m_moveSpeed = diff * GOALMULTIPLICATION;
			//Y�����̈ړ����x��0�ɂ���B
			m_moveSpeed.y = ZERO;
			//�S�[��(��])�X�e�[�g�ɑJ�ڂ���B
			m_playerState = enPlayerState_Goal;
		}
	}
}
void Player::Move_Common()
{
	//�q�b�v�h���b�v�̒��n�d�����I�����Ă�����
	if (m_dropTime >= DROPTIMEMAX)
	{
		//�ړ��G�t�F�N�g�̍Đ��J�n���Ԃ����Z����B
		m_moveTime += g_gameTime->GetFrameDeltaTime();
		//�ړ��G�t�F�N�g�̍Đ��J�n���Ԃ�0.3�b�ȏ�Ȃ�
		if (m_moveTime > MOVEEFFECTTIMEMAX)
		{
			//�_�b�V���G�t�F�N�g���Đ�����B
			DashEffect();
		}
		//X��Y�{�^���������Ă��āA�_�b�V���������Ԃ�2�b�ȉ��Ȃ�
		if (g_pad[0]->IsPress(enButtonX) && m_dashTime < DASHTIMEMAX
			|| g_pad[0]->IsPress(enButtonY) && m_dashTime < DASHTIMEMAX)
		{
			//�_�b�V���X�e�[�g�ɑJ�ڂ���B
			m_playerState = enPlayerState_Dash;
			//�X�[�p�[�_�b�V�����������G�t�F�N�g���Đ��ł���悤�ɂ���B
			Dash_Max_Effect = true;
			//�X�[�p�[�_�b�V���̉ΉԁA�ł��ՃG�t�F�N�g���Đ��ł���悤�ɂ���B
			Dash_Max_Start_Effect = true;
			
		}
		//X��Y�{�^���������Ă��āA�_�b�V���������Ԃ�2�b�ȏ�Ȃ�
		else if (g_pad[0]->IsPress(enButtonX) && m_dashTime > DASHTIMEMAX
			|| g_pad[0]->IsPress(enButtonY) && m_dashTime > DASHTIMEMAX)
		{
			//�X�[�p�[�_�b�V���X�e�[�g�ɑJ�ڂ���B
			m_playerState = enPlayerState_Dash_Max;
			
			//�X�[�p�[�_�b�V�����������G�t�F�N�g���Đ��ł���Ȃ�
			if (Dash_Max_Effect == true)
			{
				//�X�[�p�[�_�b�V�����������G�t�F�N�g���Đ�����B
				Dash_MaxEffect();
				//���ʉ���ݒ肷��B
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(m_soundlist->DASHMAX);
				//���[�v�Đ����Ȃ��B
				se->Play(false);
				//�{�����[���̐ݒ�B
				se->SetVolume(0.3f);
				Dash_Max_Effect = false;
			}
		}
		//�_�b�V�����Ă��Ȃ��Ȃ�
		else
		{
			//�����X�e�[�g�ɑJ�ڂ���B
			m_playerState = enPlayerState_Walk;
			//�����G�t�F�N�g���Đ�����B
			WalkEffect();
			//�X�[�p�[�_�b�V�����������G�t�F�N�g���Đ��ł���悤�ɂ���B
			Dash_Max_Effect = true;
		}
	}
}
void Player::Rotation()
{
		//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);

	}
	//�G�`������ɉ�]��������B
	m_modelRender.SetRotation(m_rotation);
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}
void Player::Collision()
{
	//�q�b�v�h���b�v���A��C�ړ����Ȃ�
	if (Drop == true||Fort_Idle==true||Fort_Move==true)
	{
		//�������Ȃ��B
		return;
	}
	//��]����n�ʂ̃R���W��������������B
	const auto& movecollision = g_collisionObjectManager->FindCollisionObjects("Move");
	//�R���W�����̔z���for���ŉ񂷁B
	for (auto collision : movecollision)
	{
		//��]����n�ʂ̃R���W�����Ǝ��g�̓����蔻�肪�Փ˂�����
		if (collision->IsHit(m_charaCon))
		{
			//�v���C���[����]����n�ʂɏ���Ă��邱�Ƃɂ���B
			OnGroundMove = true;
		}
		//��]����n�ʂ̃R���W�����Ǝ��g�̓����蔻�肪�Փ˂��Ă��Ȃ��Ȃ�
		else if (!collision->IsHit(m_charaCon))
		{
			//�v���C���[����]����n�ʂɏ���Ă��Ȃ����Ƃɂ���B
			OnGroundMove = false;
		}
	}
	//���S����R���W��������������B
	const auto& deadcollision = g_collisionObjectManager->FindCollisionObjects("Dead");
	//�R���W�����̔z���for���ŉ񂷁B
	for (auto collision : deadcollision)
	{
		//���S����R���W�����Ǝ��g�̓����蔻�肪�Փ˂�����
		if (collision->IsHit(m_charaCon))
		{
			//���S��Ԃɂ���B
			Dead = true;
			//���S�X�e�[�g�ɑJ�ڂ���B
			m_playerState = enPlayerState_Dead;
		}
	}
	//�u���b�N�̃R���W��������������B
	const auto& blockcollision = g_collisionObjectManager->FindCollisionObjects("Block");
	//�R���W�����̔z���for���ŉ񂷁B
	for (auto collision : blockcollision)
	{
		//�u���b�N�̃R���W�����Ǝ��g�̓����蔻�肪�Փ˂�����
		if (collision->IsHit(m_charaCon))
		{
			//Y�����̈ړ����x���O�ɂ���B
			m_moveSpeed.y = ZERO;
			//�d�͂�0�ɂ���B
			m_moveSpeed.y += GRAVITY;
			//�u���b�N�̏�ɏ���Ă����Ԃɂ���B
			OnBlock = true;
		}
		else
		{
			//�u���b�N�̏�ɏ���Ă��Ȃ���Ԃɂ���B
			OnBlock = false;
		}
		//�u���b�N�̃R���W�����Ǝ��g�̑̂̃R���W�������Փ˂�����
		if (collision->IsHit(m_collisionObject))
		{
			//x.z�����̈ړ����x��0�ɂ���B
			m_moveSpeed.x = ZERO;
			m_moveSpeed.z = ZERO;
			//�����蔻����폜����B
			m_charaCon.RemoveRigidBoby();
			//�����蔻����쐬����B
			m_charaCon.Init(
				CHARACONHITBLOCK,//���a
				CHARACONHITBLOCK,//����
				m_position//���W
			);
			//�v���C���[���u���b�N�̉�����Փ˂��Ă����Ԃɂ���B
			HitBlock = true;
		}
	}
}
void Player::ProcessCommonStateTransition()
{
	//�v���C���[������ł��Ȃ���ԂȂ�
	if (Fort_Idle == true || Fort_Move == true || Fort_Top == true || Goal == true ||
		m_playerState == enPlayerState_Dead || m_playerState == enPlayerState_Fall)
	{
		//�������Ȃ��B
		return;
	}
	//�u���b�N�̏�ɏ���Ă��āA���X�e�B�b�N�̑��삪����Ă���Ȃ�
	if (OnBlock == true&&Stick==true)
	{
		//�ړ��X�e�[�g�̏������s���B
		Move_Common();
	}
	//���X�e�B�b�N�̑��삪����Ă���Ȃ�
	else if (Stick == true)
	{
		//�ҋ@���Ԃ�0�ɂ���B
		m_idleTime = ZERO;
		//�n��ɂ���Ȃ�
		if (m_charaCon.IsOnGround())
		{
			//�ړ��X�e�[�g�̏������s���B
			Move_Common();
		}
	}
	//x.z�����̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�ҋ@�X�e�[�g�ɑJ�ڂ���B
		m_playerState = enPlayerState_Idle;
		//�ҋ@���Ԃ����Z����B
		m_idleTime += g_gameTime->GetFrameDeltaTime();
		//�ҋ@���Ԃ�6�b�ȏゾ������B
		if (m_idleTime >= IDLETIMEMAX)
		{
			//���u���ҋ@�X�e�[�g�ɑJ�ڂ���B
			m_playerState = enPlayerState_Idle2;
		}
	}
}
void Player::ProcessFortStateTransition()
{
	//�A�j���[�V�����̍Đ����I��������
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//���ʂ̃X�e�[�g�ɑJ�ڂ���B
		ProcessCommonStateTransition();
	}
}
void Player::ProcessJumpStateTransition()
{
	//�A�j���[�V�����̍Đ����I�����Ă��Ē��n���Ă�����
	if (m_modelRender.IsPlayingAnimation()== false ||
		m_charaCon.IsOnGround()||OnBlock==true)
	{
		//���ʂ̃X�e�[�g�ɑJ�ڂ���B
		ProcessCommonStateTransition();
	}
}
void Player::ProcessDropStateTransition()
{
	//���n���Ă�����
	if (m_charaCon.IsOnGround())
	{
		//�q�b�v�h���b�v(����)���������Ȃ��B
		Drop = false;
		//�q�b�v�h���b�v(�����O)���������Ȃ��B
		Stop = false;
		//���ʂ̃X�e�[�g�ɑJ�ڂ���B
		ProcessCommonStateTransition();
	}
}
void Player::ProcessGoalStateTransition()
{
	//�A�j���[�V�����̍Đ����I��������
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//�S�[��(�_���X)���\�ɂ���B
		Goal2 = true;
		//�G�t�F�N�g���Đ�����B
		ClearEffect();
	}
}
void Player::ProcessGoal2StateTransition()
{
	//A�{�^���������Ă�����
	if (g_pad[0]->IsPress(enButtonA))
	{
		//�S�[����̏������s���B
		m_game->Retry();
	}
	/*if (m_modelRender.IsPlayingAnimation() == false)
	{
		m_game->Retry();	
	}*/
}
void Player::ProcessDeadStateTransition()
{
	//�A�j���[�V�����̍Đ����I��������
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//���g���폜����B
		DeleteGO(this);
		//������������x�����s���B
		if (ReTry == true)
		{
			//�����A�Q�[���I�[�o�[�̏������s���B
			m_game->Retry();
			ReTry = false;
		}
	}
}
void Player::ManageState()
{
	switch (m_playerState)
	{
	//�ҋ@�X�e�[�g�̎��B
	case enPlayerState_Idle:
		//���ʂ̃X�e�[�g�̑J�ڏ����B
		ProcessCommonStateTransition();
		break;
	//���u���ҋ@�X�e�[�g�̎��B
	case enPlayerState_Idle2:
		//���ʂ̃X�e�[�g�̑J�ڏ����B
		ProcessCommonStateTransition();
		break;
	//�����X�e�[�g�̎��B
	case enPlayerState_Walk:
		//���ʂ̃X�e�[�g�̑J�ڏ����B
		ProcessCommonStateTransition();
		break;
	//�_�b�V���X�e�[�g�̎��B
	case enPlayerState_Dash:
		//���ʂ̃X�e�[�g�̑J�ڏ����B
		ProcessCommonStateTransition();
		break;
	//�X�[�p�[�_�b�V���X�e�[�g�̎��B
	case enPlayerState_Dash_Max:
		//���ʂ̃X�e�[�g�̑J�ڏ����B
		ProcessCommonStateTransition();
		break;
	//�W�����v�X�e�[�g�̎��B
	case enPlayerState_Jump:
		//�W�����v�X�e�[�g�̑J�ڏ����B
		ProcessJumpStateTransition();
		break;
	//�q�b�v�h���b�v�X�e�[�g�̎��B
	case enPlayerState_Drop:
		//�q�b�v�h���b�v�X�e�[�g�̑J�ڏ����B
		ProcessDropStateTransition();
		break;
	//��C�ړ�(�n��)�X�e�[�g�̎��B
	case enPlayerState_Fort_Ground:
	    //��C�ړ�(�n��)�X�e�[�g�̑J�ڏ����B
		ProcessFortStateTransition();
		break;
	//��C�ړ�(��)�X�e�[�g�̎��B
	case enPlayerState_Fort_Air:
		//���ʂ̃X�e�[�g�̑J�ڏ����B
		ProcessCommonStateTransition();
		break;
	//�S�[��(��])�X�e�[�g�̎�
	case enPlayerState_Goal:
		//�S�[��(��])�X�e�[�g�̑J�ڏ����B
		ProcessGoalStateTransition();
		break;
	//�S�[��(�_���X)�X�e�[�g�̎��B
	case enPlayerState_Goal2:
		//�S�[��(�_���X)�X�e�[�g�̑J�ڏ����B
		ProcessGoal2StateTransition();
		break; 
	//���S�X�e�[�g�̎��B
	case enPlayerState_Dead:
		//���S�X�e�[�g�̑J�ڏ����B
		ProcessDeadStateTransition();
		break;
	//�����X�e�[�g�̎��B
	case enPlayerState_Fall:
		//���S�X�e�[�g�̑J�ڏ����B
		ProcessDeadStateTransition();
		break;
	}
}
void Player::PlayAnimation()
{
	//�A�j���[�V�����̍Đ����x�B
	m_modelRender.SetAnimationSpeed(1.0f);
	////switch���B
	switch (m_playerState) {
	//�ҋ@�X�e�[�g�̎��B
	case enPlayerState_Idle:
		//�ҋ@�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.8f);
		break;
	//���u���ҋ@�X�e�[�g�̎��B
	case enPlayerState_Idle2:
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.1f);
		//���u���ҋ@�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Idle2, 0.9f);
		break;
	//�����X�e�[�g�̎��B
	case enPlayerState_Walk:
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.5f);
		//�����A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Walk, 0.8f);
		break;
	//�_�b�V���X�e�[�g�̎��B
	case enPlayerState_Dash:
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.2f);
		//�_�b�V���A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Dash, 0.8f);
		break;
	//�X�[�p�[�_�b�V���X�e�[�g�̎��B
	case enPlayerState_Dash_Max:
		//�X�[�p�[�_�b�V���A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Dash_Max, 0.8f);
		break;
	//�W�����v�X�e�[�g�̎��B
	case enPlayerState_Jump:
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(1.1f);
		//�W�����v�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Jump, 1.0f);
		break;
	//�q�b�v�h���b�v�X�e�[�g�̎��B
	case enPlayerState_Drop:
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(0.8f);
		//�q�b�v�h���b�v�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Drop, 1.0f);
		break;
	//��C�ړ�(�n��)�X�e�[�g�̎��B
	case enPlayerState_Fort_Ground:
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(0.9f);
		//��C�ړ�(�n��)�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Fort_Ground, 1.0f);
		break;
	//��C�ړ�(��)�X�e�[�g�̎��B
	case enPlayerState_Fort_Air:
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(0.9f);
		//��C�ړ�(��)�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Fort_Air, 1.0f);
		break;
	//�S�[��(��])�X�e�[�g�̎��B
	case enPlayerState_Goal:
		//�S�[��(��])�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Goal, 1.0f);
		break;
	//�S�[��(�_���X)�X�e�[�g�̎��B
	case enPlayerState_Goal2:
		//�S�[��(�_���X)�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Goal2, 1.0f);
		break;
	//���S�X�e�[�g�̎��B
	case enPlayerState_Dead:
		//�A�j���[�V�����̍Đ����x�B
		m_modelRender.SetAnimationSpeed(0.8f);
		//���S�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Dead, 1.0f);
		break;
	//�����X�e�[�g�̎��B
	case enPlayerState_Fall:
		//�����A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Fall, 1.0f);
		break;
	default:
		break;
	}
}
void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//�L�[�̖��O���uJump_Start�v�̎��B
	if (wcscmp(eventName, L"Jump_Start") == 0)
	{
		//�d�͂��W�����v�㏸���d�͂ɂ���B
		Gravity = false;
		//�G�t�F�N�g���Đ�����B
		JumpEffect();
	}
	//�L�[�̖��O���uJump_End�v�̎��B
	else if (wcscmp(eventName, L"Jump_end") == 0)
	{
		//�d�͂�ʏ�ɂ���B
		Gravity = true;
	}
	//�L�[�̖��O���uDrop_Start�v�̎��B
	else if (wcscmp(eventName, L"Drop_Start") == 0)
	{
		//�q�b�v�h���b�v�������ɂ���B
		Stop = true;
	}
	//�L�[�̖��O���uDrop_End�v�̎��B
	else if (wcscmp(eventName, L"Drop_End") == 0)
	{
		//�q�b�v�h���b�v�������̏������Ȃ��B�B
		Stop = false;
		//�q�b�v�h���b�v���ɂ���B
		Drop = true;
		//�����d�͂�^����B
		m_moveSpeed.y = -DROPGRAVITY;
	}
	//�L�[�̖��O���uDash�v�̎��B
	else if (wcscmp(eventName, L"Dash") == 0)
	{
		//���ʉ���ݒ肷��B
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(m_soundlist->DASH);
		//���[�v�Đ����Ȃ��B
		se->Play(false);
		//�{�����[���̐ݒ�B
		se->SetVolume(0.2f);
	}
	//�L�[�̖��O���uWalk�v�̎��B
	else if (wcscmp(eventName, L"Walk") == 0)
	{
		//���ʉ���ݒ肷��B
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(m_soundlist->WALK);
		//���[�v�Đ����Ȃ��B
		se->Play(false);
		//�{�����[���̐ݒ�B
		se->SetVolume(0.4f);
	}
	//�L�[�̖��O���uDash_Max_Start�v�̎��B
	else if (wcscmp(eventName, L"Dash_Max_Start") == 0)
	{ 
		//�X�[�p�[�_�b�V���̉ΉԁA�ł��Ղ̃G�t�F�N�g����x�����Đ�����B
		if (Dash_Max_Start_Effect == true)
		{
			//�X�[�p�[�_�b�V���̉ΉԂ̃G�t�F�N�g���Đ�����B
			Dash_Max_FirstEffect();
			//�X�[�p�[�_�b�V���̏ł��Ղ̃G�t�F�N�g���Đ�����B
			Dash_Max_First2Effect();
			Dash_Max_Start_Effect = false;
			//���ʉ���ݒ肷��B
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->DASHFIRST);
			//���[�v�Đ����Ȃ��B
			se->Play(false);
			//�{�����[���̐ݒ�B
			se->SetVolume(0.6f);
		}
		else
		{
			//���ʉ���ݒ肷��B
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->DMM);
			//���[�v�Đ����Ȃ��B
			se->Play(false);
			//�{�����[���̐ݒ�B
			se->SetVolume(0.08f);
		}
	}
}
void Player::Render(RenderContext& rc)
{
	//�v���C���[��`�悷��Ȃ�
	if (PlayerNotDraw == false)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
	//UI�\���J�n���Ԃ�2�b�ȏ�Ȃ�
	if (m_UITime > UITIMEMAX)
	{
		//�L�����N�^�[�A�C�R���摜��`�悷��B
		m_aiconSprite.Draw(rc);
		//�������ԉ摜��`�悷��B
		m_timerSprite.Draw(rc);
		//�������ԃt�H���g��`�悷��B
		m_timeLimitFont.Draw(rc);
		//HP�t�H���g��`�悷��B
		m_hpCountFont.Draw(rc);
	}
	//�S�[����ԂȂ�
	if (Goal == true)
	{
		//�N���A�摜��`�悷��B
		m_clear.Draw(rc);
	}
}
void Player::InitAnimation()
{
	//�A�j���[�V������ǂݍ��ށB
	m_animClips[enAnimationClip_Idle].Load("Assets/animData/Player_Idle.tka");
	m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_Idle2].Load("Assets/animData/Player_Idle2.tka");
	m_animClips[enAnimationClip_Idle2].SetLoopFlag(true);
	m_animClips[enAnimationClip_Walk].Load("Assets/animData/Player_Walk.tka");
	m_animClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_Dash].Load("Assets/animData/Player_Dash.tka");
	m_animClips[enAnimationClip_Dash].SetLoopFlag(true);
	m_animClips[enAnimationClip_Dash_Max].Load("Assets/animData/Player_Dash_Max.tka");
	m_animClips[enAnimationClip_Dash_Max].SetLoopFlag(true);
	m_animClips[enAnimationClip_Jump].Load("Assets/animData/Player_Jump.tka");
	m_animClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animClips[enAnimationClip_Drop].Load("Assets/animData/Player_HipDrop.tka");
	m_animClips[enAnimationClip_Drop].SetLoopFlag(false);
	m_animClips[enAnimationClip_Fort_Ground].Load("Assets/animData/Player_Fort_Ground.tka");
	m_animClips[enAnimationClip_Fort_Ground].SetLoopFlag(false);
	m_animClips[enAnimationClip_Fort_Air].Load("Assets/animData/Player_Fort_Air.tka");
	m_animClips[enAnimationClip_Fort_Air].SetLoopFlag(true);
	m_animClips[enAnimationClip_Goal].Load("Assets/animData/Player_Goal.tka");
	m_animClips[enAnimationClip_Goal].SetLoopFlag(false);
	m_animClips[enAnimationClip_Goal2].Load("Assets/animData/Player_Goal2.tka");
	m_animClips[enAnimationClip_Goal2].SetLoopFlag(true);
	m_animClips[enAnimationClip_Dead].Load("Assets/animData/Player_Dead.tka");
	m_animClips[enAnimationClip_Dead].SetLoopFlag(false);
	m_animClips[enAnimationClip_Fall].Load("Assets/animData/Player_Fall.tka");
	m_animClips[enAnimationClip_Fall].SetLoopFlag(false);
}
void Player::InitSprite()
{
	/// <summary>
	/// �L�����N�^�[�A�C�R��
	/// </summary>
	//�L�����N�^�[�A�C�R���摜��ǂݍ��ށB
	m_aiconSprite.Init("Assets/sprite/aicon.DDS", 200, 200);
	//�s�{�b�g��ݒ肷��B
	m_aiconSprite.SetPivot(Vector2(ATCSPRITEPIVOT));
	//���W��ݒ肷��B
	m_aiconSprite.SetPosition(Vector3(AICONSPRITEPOS));
	//�X�V�����B
	m_aiconSprite.Update();
	/// <summary>
	/// �������ԉ摜
	/// </summary>
	//�������ԉ摜��ǂݍ��ށB
	m_timerSprite.Init("Assets/sprite/timer.DDS", 80, 80);
	//�s�{�b�g��ݒ肷��B
	m_timerSprite.SetPivot(Vector2(ATCSPRITEPIVOT));
	//���W��ݒ肷��B
	m_timerSprite.SetPosition(Vector3(TIMERSPRITEPOS));
	//�X�V�����B
	m_timerSprite.Update();
	/// <summary>
	/// �N���A�摜
	/// </summary>
	//�N���A�摜��ǂݍ��ށB
	m_clear.Init("Assets/sprite/clear.DDS", 1000, 1100);
	//�s�{�b�g��ݒ肷��B
	m_clear.SetPivot(Vector2(ATCSPRITEPIVOT));
	//���W��ݒ肷��B
	m_clear.SetPosition(Vector3(CLEARSPRITEPOS));
	//�X�V�����B
	m_clear.Update();
}
void Player::HP()
{
	//���݂�HP��\������B
	m_hpCountwst = std::to_wstring(m_game->HP);
	m_hpCountFont.SetText(m_hpCountwst.c_str());
	//���W��ݒ肷��B
	m_hpCountFont.SetPosition(HPFONTPOS);
	//�s�{�b�g��ݒ肷��B
	m_hpCountFont.SetPivot(Vector2(HPFONTPIVOT));
	//�傫����ݒ肷��B
	m_hpCountFont.SetScale(HPFONTSCALE);
	//�e�̃p�����[�^�[��ݒ肷��B
	m_hpCountFont.SetShadowParam(true, HPFONTOFFSET, g_vec4White);
	//HP��1�Ȃ�
	if (m_game->HP <= HPFONTCOLORRED)
	{
		//������Ԃɂ���B
		m_hpCountFont.SetColor(g_vec4Red);
	}
	//HP��3�ȉ��Ȃ�
	else if (m_game->HP <= HPFONTCOLORYELLOW)
	{
		//���������F�ɂ���B
		m_hpCountFont.SetColor(g_vec4Yellow);
	}
	//HP���T�ȉ��Ȃ�
	else {
		//�����𔒂ɂ���B
		m_hpCountFont.SetColor(g_vec4Gray);
	}
}
void Player::TimeLimit()
{
	//�������Ԃ�int�^�ɂ���B
	Game_Timer = m_game->m_gameTime;
	//���݂̐������Ԃ�\������B
	m_timeLimittwst = std::to_wstring(Game_Timer);
	m_timeLimitFont.SetText(m_timeLimittwst.c_str());
	//���W��ݒ肷��B
	m_timeLimitFont.SetPosition(TIMEFONTPOS);
	//�s�{�b�g��ݒ肷��B
	m_timeLimitFont.SetPivot(Vector2(TIMEFONTPIVOT));
	//�傫����ݒ肷��B
	m_timeLimitFont.SetScale(TIMEFONTSCALE);
	//�e�̃p�����[�^�[��ݒ肷��B
	m_timeLimitFont.SetShadowParam(true, TIMEFONTOFFSET, g_vec4White);
	//�������Ԃ�30�b�ȉ��Ȃ�
	if (Game_Timer <= TIMEFONTCOLORRED)
	{
		//������Ԃɂ���B
		m_timeLimitFont.SetColor(g_vec4Red);
	}
	//�������Ԃ�100�b�ȉ��Ȃ�
	else if (Game_Timer <= TIMEFONTCOLORYELLOW)
	{
		//�������I�����W�F�ɂ���B
		m_timeLimitFont.SetColor(g_vec4Orange);
	}
	//�������Ԃ�300�b�ȉ��Ȃ�
	else {
		//�����𔒂ɂ���B
		m_timeLimitFont.SetColor(g_vec4Gray);
	}
}
void Player::DashEffect()
{
	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->MOVE);
	//���W��ݒ肷��B
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(WALKDASHEFFECTSCALE);
	//�G�t�F�N�g���Đ�����B
	m_effectEmitter->Play();
}
void Player::WalkEffect()
{
	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->WALK);
	//���W��ݒ肷��B
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(WALKDASHEFFECTSCALE);
	//�G�t�F�N�g���Đ�����B
	m_effectEmitter->Play();
}
void Player::Dash_MaxEffect()
{
	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->DASHFIRST);
	//���W��ݒ肷��B
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(WALKDASHEFFECTSCALE);
	//�G�t�F�N�g���Đ�����B
	m_effectEmitter->Play();
}
void Player::Dash_Max_FirstEffect()
{
	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->DMF);
	//���W��ݒ肷��B
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(DMFEFFECTSCALE);
	//�G�t�F�N�g���Đ�����B
	m_effectEmitter->Play();
}
void Player::Dash_Max_First2Effect()
{
	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->DMF2);
	//���W��ݒ肷��B
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(DMF2EFFECTSCALE);
	//�G�t�F�N�g���Đ�����B
	m_effectEmitter->Play();
}
void Player::JumpEffect()
{
	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->JUMP);
	//���W��ݒ肷��B
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(JUMPEFFECTSCALE);
	m_effectEmitter->Play();
}
void Player::Drop_EndEffect()
{
	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->DROP);
	//���W��ݒ肷��B
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(DROPEFFECTSCALE);
	//�G�t�F�N�g���Đ�����B
	m_effectEmitter->Play();
}
void Player::ClearEffect()
{
	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->CLEAR);
	//���W��ݒ肷��B
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(CLEAREFFECTSCALE);
	//�G�t�F�N�g���Đ�����B
	m_effectEmitter->Play();
}
void Player::HedCollision() 
{
	//�R���W�����I�u�W�F�N�g���쐬����B
	auto Hedcollision = NewGO<CollisionObject>(0);
	//���W��ݒ肷��B
	Vector3 m_boxposition = m_position;
	m_boxposition.y = m_position.y + HEDCOLLISIONPOSY;
	//�{�b�N�X��̃R���W�������쐬����B
	Hedcollision->CreateBox(
		m_boxposition,//���W
		Quaternion::Identity,//��]
		HEDCOLLISIONSCALE//�傫��
	);
	//���O��Head�ɂ���B
	Hedcollision->SetName("Head");
}
void Player::LegCollision()
{
	//�R���W�����I�u�W�F�N�g���쐬����B
	auto Legcollision = NewGO<CollisionObject>(0);
	//���W��ݒ肷��B
	Vector3 m_boxposition = m_position;
	m_boxposition.y = m_position.y - LEGCOLLISIONPOSY;
	//�{�b�N�X��̃R���W�������쐬����B
	Legcollision->CreateBox(
		m_boxposition,//���W�B
		Quaternion::Identity,//��]
		LEGCOLLISIONSCALE//�傫��
	);
	//���O��Leg�ɂ���B
	Legcollision->SetName("Leg");
}
void Player::HipCollision()
{
	//�R���W�����I�u�W�F�N�g���쐬����B
	auto HipCollision = NewGO<CollisionObject>(0);
	//���W��ݒ肷��B
	Vector3 m_boxposition = m_position;
	m_boxposition.y = m_position.y - HIPCOLLISIONPOSY;
	//�{�b�N�X��̃R���W�������쐬����B
	HipCollision->CreateBox(
		m_boxposition,
		Quaternion::Identity,
		HIPCOLLISIONSCALE);
	//���O��Hip�ɂ���B
	HipCollision->SetName("Hip");
}