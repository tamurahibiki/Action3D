#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Ground.h"
#include "Tree.h"
#include "Fence.h"
#include "FenceHalf.h"
#include "Stairs.h"
#include "Block.h"
#include "FlowerBed.h"
#include "WoodenBox.h"
#include "Grass.h"
#include "Flower.h"
#include "Shrub.h"
#include "Pebble.h"
#include "Signboard.h"
#include "Wood_Road.h"
#include "Windmill.h"
#include "Pipe.h"
#include "Rock_Big.h"
#include "GroundMove.h"
#include "GroundRoad.h"
#include "Fort.h"
#include "FortTop.h"
#include "Ring.h"
#include "Bard.h"
#include "Enemy_Green.h"
#include "Enemy_Red.h"
#include "Enemy_Yellow.h"
#include "GoalPoint.h"
#include "GameCamera.h"
#include "HitBox.h"
#include "Default.h"
#include "Forward.h"
#include "SkyCube.h"
#include "Fade.h"
#include "Title.h"
#include "EffectList.h"
#include "SoundList.h"

namespace
{
	const int ZERO = 0;//�[��
}
namespace App {
	Game::Game() {}
	Game::~Game()
	{
		//////////////////////////////////////
		//��������v���C���[�̈ʒu��񂪕K�v�łȂ��I�u�W�F�N�g���폜����B
		//////////////////////////////////////
		DeleteGO(m_sky);
		DeleteGO(FindGO<Ground>("ground"));
		DeleteGO(FindGO<GroundRoad>("groundroad"));
		DeleteGO(FindGO<GroundMove>("groundmove"));
		DeleteGO(FindGO<Stairs>("stairs"));
		DeleteGO(FindGO<Windmill>("windmill"));
		const auto& blocks = FindGOs<Block>("block");
		for (auto block : blocks)
		{
			DeleteGO(block);
		}
		const auto& shrubs = FindGOs<Shrub>("shrub");
		for (auto shrub : shrubs)
		{
			DeleteGO(shrub);
		}
		const auto& pebbles = FindGOs<Pebble>("pebble");
		for (auto pebble : pebbles)
		{
			DeleteGO(pebble);
		}
		const auto& pipes = FindGOs<Pipe>("pipe");
		for (auto pipe : pipes)
		{
			DeleteGO(pipe);
		}
		const auto& fences = FindGOs<Fence>("fence");
		for (auto fence : fences)
		{
			DeleteGO(fence);
		}
		const auto& fencehalfs = FindGOs<FenceHalf>("fencehalf");
		for (auto fencehalf : fencehalfs)
		{
			DeleteGO(fencehalf);
		}
		const auto& flowers = FindGOs<Flower>("flower");
		for (auto flower : flowers)
		{
			DeleteGO(flower);
		}
		const auto& flowerbeds = FindGOs<FlowerBed>("flowerbed");
		for (auto flowerbed : flowerbeds)
		{
			DeleteGO(flowerbed);
		}
		const auto& grasses = FindGOs<Grass>("grass");
		for (auto grass : grasses)
		{
			DeleteGO(grass);
		}
		const auto& hitboxs = FindGOs<HitBox>("hitbox");
		for (auto hitbox : hitboxs)
		{
			DeleteGO(hitbox);
		}
		const auto& rock_bigs = FindGOs<Rock_Big>("rock_big");
		for (auto rock_big : rock_bigs)
		{
			DeleteGO(rock_big);
		}
		const auto& rings = FindGOs<Ring>("ring");
		for (auto ring : rings)
		{
			DeleteGO(ring);
		}
		const auto& signboards = FindGOs<Signboard>("signboard");
		for (auto signboard : signboards)
		{
			DeleteGO(signboard);
		}
		const auto& trees = FindGOs<Tree>("tree");
		for (auto tree : trees)
		{
			DeleteGO(tree);
		}
		const auto& wood_roads = FindGOs<Wood_Road>("wood_road");
		for (auto wood_road : wood_roads)
		{
			DeleteGO(wood_road);
		}
		const auto& woodenboxs = FindGOs<WoodenBox>("woodenbox");
		for (auto woodenbox : woodenboxs)
		{
			DeleteGO(woodenbox);
		}
		//////////////////////////////////////
		//�v���C���[�̈ʒu��񂪕K�v�łȂ��I�u�W�F�N�g���폜����̂͂����܂ŁB
		//////////////////////////////////////
		//BGM���폜����B
		DeleteGO(m_bgm);
	}
	bool Game::Start()
	{
		//��̃I�u�W�F�N�g���쐬����B
		m_sky = NewGO<SkyCube>(0, "sky");
		//�v���C���[�̃I�u�W�F�N�g���쐬����B
		m_player = NewGO<Player>(0, "player");
		//���x�����\�z����B
		m_levelRender.Init("Assets/level3D/level1.tkl",
			[&](LevelObjectData& objData) {
				//���O��ground��������
				if (objData.EqualObjectName(L"ground") == true) {
					//�n�`�̃I�u�W�F�N�g���쐬����B
					Ground* bg = NewGO<Ground>(0, "ground");
					//���W��ݒ肷��B
					bg->SetPosition(objData.position);
					//�傫����ݒ肷��B
					bg->SetScale(objData.scale);
					//��]��ݒ肷��B
					bg->SetRotation(objData.rotation);
					return true;
				}
				//���O��groundmove��������
				else if (objData.EqualObjectName(L"groundmove") == true) {
					//��]����n�ʂ̃I�u�W�F�N�g���쐬����B
					GroundMove* groundmove = NewGO<GroundMove>(0, "groundmove");
					//���W��ݒ肷��B
					groundmove->SetPosition(objData.position);
					//�傫����ݒ肷��B
					groundmove->SetScale(objData.scale);
					//��]��ݒ肷��B
					groundmove->SetRotation(objData.rotation);
					return true;
				}
				//���O��tree��������
				else if (objData.EqualObjectName(L"tree") == true) {
					//�؂̃I�u�W�F�N�g���쐬����B
					Tree* tree = NewGO<Tree>(0, "tree");
					//���W��ݒ肷��B
					tree->SetPosition(objData.position);
					//�傫����ݒ肷��B
					tree->SetScale(objData.scale);
					//��]��ݒ肷��B
					tree->SetRotation(objData.rotation);
					return true;
				}
				//���O��shrub��������
				else if (objData.EqualObjectName(L"shrub") == true) {
					//��؂̃I�u�W�F�N�g���쐬����B
					Shrub* shrub = NewGO<Shrub>(0, "shrub");
					//���W��ݒ肷��B
					shrub->SetPosition(objData.position);
					//�傫����ݒ肷��B
					shrub->SetScale(objData.scale);
					//��]��ݒ肷��B
					shrub->SetRotation(objData.rotation);
					return true;
				}
				//���O��grass��������
				else if (objData.EqualObjectName(L"grass") == true) {
					//���̃I�u�W�F�N�g���쐬����B
					Grass* grass = NewGO<Grass>(0, "grass");
					//���W��ݒ肷��B
					grass->SetPosition(objData.position);
					//�傫����ݒ肷��B
					grass->SetScale(objData.scale);
					//��]��ݒ肷��B
					grass->SetRotation(objData.rotation);
					return true;
				}
				//���O��flower��������
				else if (objData.EqualObjectName(L"flower") == true) {
					//�Ԃ̃I�u�W�F�N�g���쐬����B
					Flower* flower = NewGO<Flower>(0, "flower");
					//���W��ݒ肷��B
					flower->SetPosition(objData.position);
					//�傫����ݒ肷��B
					flower->SetScale(objData.scale);
					//��]��ݒ肷��B
					flower->SetRotation(objData.rotation);
					return true;
				}
				//���O��flowerbed��������
				else if (objData.EqualObjectName(L"flowerbed") == true) {
					//�Ԓd�̃I�u�W�F�N�g���쐬����B
					FlowerBed* flowerbed = NewGO<FlowerBed>(0, "flowerbed");
					//���W��ݒ肷��B
					flowerbed->SetPosition(objData.position);
					//�傫����ݒ肷��B
					flowerbed->SetScale(objData.scale);
					//��]��ݒ肷��B
					flowerbed->SetRotation(objData.rotation);
					return true;
				}
				//���O��pebble��������
				else if (objData.EqualObjectName(L"pebble") == true) {
					//���΂̃I�u�W�F�N�g���쐬����B
					Pebble* pebble = NewGO<Pebble>(0, "pebble");
					//���W��ݒ肷��B
					pebble->SetPosition(objData.position);
					//�傫����ݒ肷��B
					pebble->SetScale(objData.scale);
					//��]��ݒ肷��B
					pebble->SetRotation(objData.rotation);
					return true;
				}
				//���O��rock_big��������
				else if (objData.EqualObjectName(L"rock_big") == true) {
					//�傫�Ȑ΂̃I�u�W�F�N�g���쐬����B
					Rock_Big* rock_big = NewGO<Rock_Big>(0, "rock_big");
					//���W��ݒ肷��B
					rock_big->SetPosition(objData.position);
					//�傫����ݒ肷��B
					rock_big->SetScale(objData.scale);
					//��]��ݒ肷��B
					rock_big->SetRotation(objData.rotation);
					return true;
				}
				//���O��fence��������
				else if (objData.EqualObjectName(L"fence") == true) {
					//�t�F���X�̃I�u�W�F�N�g���쐬����B
					Fence* fence = NewGO<Fence>(0, "fence");
					//���W��ݒ肷��B
					fence->SetPosition(objData.position);
					//�傫����ݒ肷��B
					fence->SetScale(objData.scale);
					//��]��ݒ肷��B
					fence->SetRotation(objData.rotation);
					return true;
				}
				//���O��fencehalf��������
				else if (objData.EqualObjectName(L"fencehalf") == true) {
					//�n�[�t�t�F���X�̃I�u�W�F�N�g���쐬����B
					FenceHalf* fencehalf = NewGO<FenceHalf>(0, "fencehalf");
					//���W��ݒ肷��B
					fencehalf->SetPosition(objData.position);
					//�傫����ݒ肷��B
					fencehalf->SetScale(objData.scale);
					//��]��ݒ肷��B
					fencehalf->SetRotation(objData.rotation);
					return true;
				}
				//���O��stairs��������
				else if (objData.EqualObjectName(L"stairs") == true) {
					//�K�i�̃I�u�W�F�N�g���쐬����B
					Stairs* stairs = NewGO<Stairs>(0, "stairs");
					//���W��ݒ肷��B
					stairs->SetPosition(objData.position);
					//�傫����ݒ肷��B
					stairs->SetScale(objData.scale);
					//��]��ݒ肷��B
					stairs->SetRotation(objData.rotation);
					return true;
				}
				//���O��signboard��������
				else if (objData.EqualObjectName(L"signboard") == true) {
					//�Ŕ̃I�u�W�F�N�g���쐬����B
					Signboard* signboard = NewGO<Signboard>(0, "signboard");
					//���W��ݒ肷��B
					signboard->SetPosition(objData.position);
					//�傫����ݒ肷��B
					signboard->SetScale(objData.scale);
					//��]��ݒ肷��B
					signboard->SetRotation(objData.rotation);
					return true;
				}
				//���O��pipe��������
				else if (objData.EqualObjectName(L"pipe") == true) {
					//�y�ǂ̃I�u�W�F�N�g���쐬����B
					Pipe* pipe = NewGO<Pipe>(0, "pipe");
					//���W��ݒ肷��B
					pipe->SetPosition(objData.position);
					//�傫����ݒ肷��B
					pipe->SetScale(objData.scale);
					//��]��ݒ肷��B
					pipe->SetRotation(objData.rotation);
					return true;
				}
				//���O��woodenbox��������
				else if (objData.EqualObjectName(L"woodenbox") == true) {
					//�ؔ��̃I�u�W�F�N�g���쐬����B
					WoodenBox* woodenbox = NewGO<WoodenBox>(0, "woodenbox");
					//���W��ݒ肷��B
					woodenbox->SetPosition(objData.position);
					//�傫����ݒ肷��B
					woodenbox->SetScale(objData.scale);
					//��]��ݒ肷��B
					woodenbox->SetRotation(objData.rotation);
					return true;
				}
				//���O��wood_road��������
				else if (objData.EqualObjectName(L"wood_road") == true) {
					//�ؐ��̓��̃I�u�W�F�N�g���쐬����B
					Wood_Road* wood_road = NewGO<Wood_Road>(0, "wood_road");
					//���W��ݒ肷��B
					wood_road->SetPosition(objData.position);
					//�傫����ݒ肷��B
					wood_road->SetScale(objData.scale);
					//��]��ݒ肷��B
					wood_road->SetRotation(objData.rotation);
					return true;
				}
				//���O��windmill��������
				else if (objData.EqualObjectName(L"windmill") == true) {
					//���Ԃ̃I�u�W�F�N�g���쐬����B
					Windmill* windmill = NewGO<Windmill>(0, "windmill");
					//���W��ݒ肷��B
					windmill->SetPosition(objData.position);
					//�傫����ݒ肷��B
					windmill->SetScale(objData.scale);
					//��]��ݒ肷��B
					windmill->SetRotation(objData.rotation);
					return true;
				}
				//���O��block��������
				else if (objData.EqualObjectName(L"block") == true) {
					//�u���b�N�̃I�u�W�F�N�g���쐬����B
					Block* block = NewGO<Block>(0, "block");
					//���W��ݒ肷��B
					block->SetPosition(objData.position);
					//�傫����ݒ肷��B
					block->SetScale(objData.scale);
					//��]��ݒ肷��B
					block->SetRotation(objData.rotation);
					return true;
				}
				//���O��goalpoint��������
				else if (objData.EqualObjectName(L"goalpoint") == true) {
					//�S�[���|�C���g�̃I�u�W�F�N�g���쐬����B
					GoalPoint* goalpoint = NewGO<GoalPoint>(0, "goalpoint");
					//���W��ݒ肷��B
					goalpoint->SetPosition(objData.position);
					//�傫����ݒ肷��B
					goalpoint->SetScale(objData.scale);
					//��]��ݒ肷��B
					goalpoint->SetRotation(objData.rotation);
					return true;
				}
				//���O��fort��������
				else if (objData.EqualObjectName(L"fort") == true) {
					//��C�̃I�u�W�F�N�g���쐬����B
					Fort* fort = NewGO<Fort>(0, "fort");
					//���W��ݒ肷��B
					fort->SetPosition(objData.position);
					//�傫����ݒ肷��B
					fort->SetScale(objData.scale);
					//��]��ݒ肷��B
					fort->SetRotation(objData.rotation);
					return true;
				}
				//���O��forttop��������
				else if (objData.EqualObjectName(L"forttop") == true) {
					//��C�ړ��̒��_�|�C���g�̃I�u�W�F�N�g���쐬����B
					FortTop* forttop = NewGO<FortTop>(0, "forttop");
					//���W��ݒ肷��B
					forttop->SetPosition(objData.position);
					//�傫����ݒ肷��B
					forttop->SetScale(objData.scale);
					//��]��ݒ肷��B
					forttop->SetRotation(objData.rotation);
					return true;
				}
				//���O��groundroad��������
				else if (objData.EqualObjectName(L"groundroad") == true) {
					//��C����̑����̃I�u�W�F�N�g���쐬����B
					GroundRoad* groundroad = NewGO<GroundRoad>(0, "groundroad");
					//���W��ݒ肷��B
					groundroad->SetPosition(objData.position);
					//�傫����ݒ肷��B
					groundroad->SetScale(objData.scale);
					//��]��ݒ肷��B
					groundroad->SetRotation(objData.rotation);
					return true;
				}
				//���O��ring��������
				else if (objData.EqualObjectName(L"ring") == true) {
					//�����O�̃I�u�W�F�N�g���쐬����B
					Ring* ring = NewGO<Ring>(0, "ring");
					//���W��ݒ肷��B
					ring->SetPosition(objData.position);
					//�傫����ݒ肷��B
					ring->SetScale(objData.scale);
					//��]��ݒ肷��B
					ring->SetRotation(objData.rotation);
					return true;
				}
				//���O��bard��������
				else if (objData.EqualObjectName(L"bard") == true) {
					//���̃I�u�W�F�N�g���쐬����B
					Bard* bard = NewGO<Bard>(0, "bard");
					//���W��ݒ肷��B
					bard->SetPosition(objData.position);
					//�傫����ݒ肷��B
					bard->SetScale(objData.scale);
					//��]��ݒ肷��B
					bard->SetRotation(objData.rotation);
					return true;
				}
				//���O��enemy_green��������
				else if (objData.EqualObjectName(L"enemy_green") == true) {
					//�������U���G�l�~�[�̃I�u�W�F�N�g���쐬����B
					Enemy_Green* enemy_green = NewGO<Enemy_Green>(0, "enemy_green");
					//���W��ݒ肷��B
					enemy_green->SetPosition(objData.position);
					//�傫����ݒ肷��B
					enemy_green->SetScale(objData.scale);
					//��]��ݒ肷��B
					enemy_green->SetRotation(objData.rotation);
					return true;
				}
				//���O��enemy_red��������
				else if (objData.EqualObjectName(L"enemy_red") == true) {
					//�ǂ������Ă���G�l�~�[�̃I�u�W�F�N�g���쐬����B
					Enemy_Red* enemy_red = NewGO<Enemy_Red>(0, "enemy_red");
					//���W��ݒ肷��B
					enemy_red->SetPosition(objData.position);
					//�傫����ݒ肷��B
					enemy_red->SetScale(objData.scale);
					//��]��ݒ肷��B
					enemy_red->SetRotation(objData.rotation);
					return true;
				}
				//���O��enemy_yellow��������
				else if (objData.EqualObjectName(L"enemy_yellow") == true) {
					//���ł���G�l�~�[�̃I�u�W�F�N�g���쐬����B
					Enemy_Yellow* enemy_yellow = NewGO<Enemy_Yellow>(0, "enemy_yellow");
					//���W��ݒ肷��B
					enemy_yellow->SetPosition(objData.position);
					//�傫����ݒ肷��B
					enemy_yellow->SetScale(objData.scale);
					//��]��ݒ肷��B
					enemy_yellow->SetRotation(objData.rotation);
					return true;
				}
				//���O��hitbox��������
				else if (objData.EqualObjectName(L"hitbox") == true) {
					//�����Ȃ������蔻��̃I�u�W�F�N�g���쐬����B
					HitBox* hitbox = NewGO<HitBox>(0, "hitbox");
					//���W��ݒ肷��B
					hitbox->SetPosition(objData.position);
					//�傫����ݒ肷��B
					hitbox->SetScale(objData.scale);
					//��]��ݒ肷��B
					hitbox->SetRotation(objData.rotation);
					return true;
				}
				//���O��default��������
				else if (objData.EqualObjectName(L"default") == true) {
					//�ʏ�J�����ɕύX����|�C���g�̃I�u�W�F�N�g���쐬����B
					Default* defaultd = NewGO<Default>(0, "default");
					//���W��ݒ肷��B
					defaultd->SetPosition(objData.position);
					//�傫����ݒ肷��B
					defaultd->SetScale(objData.scale);
					//��]��ݒ肷��B
					defaultd->SetRotation(objData.rotation);
					return true;
				}
				//���O��forward��������
				else if (objData.EqualObjectName(L"forward") == true) {
					//���s���J�����ɕύX����|�C���g�̃I�u�W�F�N�g���쐬����B
					Forward* forward = NewGO<Forward>(0, "forward");
					//���W��ݒ肷��B
					forward->SetPosition(objData.position);
					//�傫����ݒ肷��B
					forward->SetScale(objData.scale);
					//��]��ݒ肷��B
					forward->SetRotation(objData.rotation);
					return true;
				}
				return true;
			});
		//�G�t�F�N�g��ǂݍ��ށB
		m_effectlist = NewGO<EffectList>(0, "effectlist");
		//����ǂݍ��ށB
		m_soundlist = FindGO<SoundList>("soundlist");

		//BGM���Đ�����B
		m_bgm = NewGO<SoundSource>(0);
		m_bgm->Init(m_soundlist->GAMEBGM);
		//���[�v����B
		m_bgm->Play(true);
		//�{�����[����ݒ肷��B
		m_bgm->SetVolume(0.04f);

		m_fade = FindGO<Fade>("fade");
		m_fade->StartFadeIn();

		return true;
	}
	void Game::Update()
	{
		//m_player->RainEffect();
		//�����t�F�[�h�A�E�g���Ȃ�
		if (m_isWaitFadeout)
		{
			//�t�F�[�h���łȂ��Ȃ�
			if (!m_fade->IsFade())
			{
				//�t�F�[�h�C������B
				m_fade->StartFadeIn();
			}
		}
		//�������Ԃ̏���
		/*�v���C���[�̏�Ԃ����S���Ă��Ȃ��āA�S�[�����Ă��Ȃ��āA
		UI���\������Ă���Ȃ�*/
		if (m_player->Dead == false && m_player->Goal == false
			&& m_player->m_UITime > 2.0f)
		{
			//�������Ԃ����炵�Ă����B
			m_gameTime -= g_gameTime->GetFrameDeltaTime();
		}
		//���Ԓn�_�ɓ��B���Ă���Ȃ�
		if (Try == true)
		{
			//////////////////////////////////////
			////���������C�ړ���ɕK�v�Ȃ��I�u�W�F�N�g���폜����B
			//////////////////////////////////////
			DeleteGO(FindGO<GroundRoad>("groundroad"));
			DeleteGO(FindGO<GroundMove>("groundmove"));
			DeleteGO(FindGO<Stairs>("stairs"));
			DeleteGO(FindGO<Windmill>("windmill"));
			DeleteGO(FindGO<Fort>("fort"));
			const auto& rock_bigs = FindGOs<Rock_Big>("rock_big");
			for (auto rock_big : rock_bigs)
			{
				DeleteGO(rock_big);
			}
			const auto& rings = FindGOs<Ring>("ring");
			for (auto ring : rings)
			{
				DeleteGO(ring);
			}
			const auto& pipes = FindGOs<Pipe>("pipe");
			for (auto pipe : pipes)
			{
				DeleteGO(pipe);
			}
			const auto& shrubs = FindGOs<Shrub>("shrub");
			for (auto shrub : shrubs)
			{
				DeleteGO(shrub);
			}
			//////////////////////////////////////
			////��C�ړ���ɕK�v�Ȃ��I�u�W�F�N�g���폜����̂͂����܂ŁB
			//////////////////////////////////////
		}

		//�����I���R�}���h*���d���t�F�X�^�p
		if (g_pad[0]->IsPress(enButtonRB1) && g_pad[0]->IsPress(enButtonLB1) &&
			g_pad[0]->IsPress(enButtonA) && g_pad[0]->IsPress(enButtonB)
			&& g_pad[0]->IsPress(enButtonStart))
		{
			m_fade->StartFadeOut();
			DeleteGO(m_player);
			DeleteModel();
			return;
		}
		//�������X�|�[���R�}���h*���d���t�F�X�^�p
		if (g_pad[0]->IsPress(enButtonRB1) && g_pad[0]->IsPress(enButtonLB1) &&
			g_pad[0]->IsPress(enButtonA) && g_pad[0]->IsPress(enButtonB)
			&& g_pad[0]->IsPress(enButtonSelect))
		{
			m_fade->StartFadeOut();
			DeleteGO(FindGO<GameCamera>("gamecamera"));
			DeleteGO(m_player);
			m_player = NewGO<Player>(0, "player");
			m_player->Dead = false;
			m_player->Fall = false;
			m_isWaitFadeout = true;
			return;
		}
	}
	void Game::Retry()
	{
		//�v���C���[���S�[�����Ă���Ȃ�
		if (m_player->Goal == true)
		{
			//�v���C���[���폜����B
			DeleteGO(m_player);
			//�t�F�[�h�A�E�g�ɂ���B
			m_fade->StartFadeOut();
			//��Ɉꕔ�̃��f�����폜����B
			DeleteModel();
			return;
		}
		else
		{
			//�������Ԃ�0�b�Ȃ�
			if (m_gameTime <= 0)
			{
				//�v���C���[���폜����B
				DeleteGO(m_player);
				//�t�F�[�h�A�E�g�ɂ���B
				m_fade->StartFadeOut();
				//��Ɉꕔ�̃��f�����폜����B
				DeleteModel();
				return;
			}
			//�̗́i�c�@�j���P���炷
			HP--;
			//�̗́i�c�@�j���c���Ă���Ȃ�
			if (HP > ZERO)
			{
				//�t�F�[�h�A�E�g�ɂ���B
				m_fade->StartFadeOut();
				//�Q�[���J�������폜����B
				DeleteGO(FindGO<GameCamera>("gamecamera"));
				//�v���C���[�̃I�u�W�F�N�g���쐬����B
				m_player = NewGO<Player>(0, "player");
				//�v���C���[�̎��S��Ԃ��������Ȃ��B
				m_player->Dead = false;
				//�v���C���[�̗�����Ԃ��������Ȃ��B
				m_player->Fall = false;
				////�t�F�[�h�A�E�g���ɂ���B
				m_isWaitFadeout = true;
			}
			//�̗́i�c�@�j���c���Ă��Ȃ��Ȃ�
			else
			{
				//�t�F�[�h�A�E�g�ɂ���B
				m_fade->StartFadeOut();
				//��Ɉꕔ�̃��f�����폜����B
				DeleteModel();
			}
		}
	}
	void Game::DeleteModel()
	{
		//////////////////////////////////////
		//��������v���C���[�̈ʒu��񂪕K�v�ȃI�u�W�F�N�g���폜����B
		//////////////////////////////////////
		DeleteGO(FindGO<GameCamera>("gamecamera"));
		DeleteGO(FindGO<FortTop>("forttop"));
		DeleteGO(FindGO<Fort>("fort"));
		DeleteGO(FindGO<GoalPoint>("goalpoint"));
		const auto& bards = FindGOs<Bard>("bard");
		for (auto bard : bards)
		{
			DeleteGO(bard);
		}
		const auto& pebbles = FindGOs<Pebble>("pebble");
		for (auto pebble : pebbles)
		{
			DeleteGO(pebble);
		}
		const auto& enemy_greens = FindGOs<Enemy_Green>("enemy_green");
		for (auto enemy_green : enemy_greens)
		{
			DeleteGO(enemy_green);
		}
		const auto& enemy_reds = FindGOs<Enemy_Red>("enemy_red");
		for (auto enemy_red : enemy_reds)
		{
			DeleteGO(enemy_red);
		}
		const auto& enemy_yellows = FindGOs<Enemy_Yellow>("enemy_yellow");
		for (auto enemy_yellow : enemy_yellows)
		{
			DeleteGO(enemy_yellow);
		}
		const auto& defaults = FindGOs<Default>("default");
		for (auto defaultd : defaults)
		{
			DeleteGO(defaultd);
		}
		const auto& forwards = FindGOs<Forward>("forward");
		for (auto forward : forwards)
		{
			DeleteGO(forward);
		}
		//////////////////////////////////////
		//�v���C���[�̏�񂪈ʒu�K�v�ȃI�u�W�F�N�g���폜����̂͂����܂ŁB
		//////////////////////////////////////
		//�^�C�g�����쐬����B
		NewGO<Title>(0, "title");
		//���g���폜����
		DeleteGO(this);
		//�t�F�[�h�A�E�g���ɂ���B
		m_isWaitFadeout = true;
	}
}