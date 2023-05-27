#pragma once
#include "level3D/Level.h"
#include "time/GameTime.h"

/// <summary>
/// �Q�[���N���X
/// </summary>
namespace App {
	class Player;
	class Ground;
	class Tree;
	class Fence;
	class FenceHalf;
	class Stairs;
	class Block;
	class FlowerBed;
	class WoodenBox;
	class Grass;
	class Flower;
	class Shrub;
	class Pebble;
	class Signboard;
	class Wood_Road;
	class Windmill;
	class Pipe;
	class Rock_Big;
	class GroundMove;
	class GroundRoad;
	class Fort;
	class FortTop;
	class Ring;
	class Bard;
	class Enemy_Green;
	class Enemy_Red;
	class Enemy_Yellow;
	class GoalPoint;
	class GameCamera;
	class Default;
	class ForWard;
	class HitBox;
	class Fade;
	class EffectList;
	class SoundList;
	class Game :public IGameObject
	{
	public:
		Game();
		~Game();
		bool Start();
		void Update();
		//�v���C���[�̃S�[���A���S��̏���
		void Retry();
		//�v���C���[�̈ʒu��񂪕K�v�ȃI�u�W�F�N�g���폜����B
		void DeleteModel();
		//�̗�
		int    HP = 5;
		/// <summary>
		/// ���Ԓn�_�ɓ��B���Ă��邩�B
		/// </summary>
		/// <returns>���Ԓn�_�ɓ��B���Ă���Ȃ�true�B</returns>
		bool   Try = false;
		/// <summary>
		///�v���C���[�����܂ꂽ���ォ�B
		/// </summary>
		/// <returns>�v���C���[�����܂ꂽ����Ȃ�true�B</returns>
		bool   PlayerSpawn = true;
		float  m_gameTime = 300.0f;//��������

	private:
		/// <summary>
		///�t�F�[�h�A�E�g�����B
		/// </summary>
		/// <returns>�t�F�[�h�A�E�g���Ȃ�true�B</returns>
		bool             m_isWaitFadeout = false;
		ModelRender      m_modelRender;                    //���f�������_�[
		GameCamera* m_gameCamera;                     //�Q�[���J����
		Level            m_levelRender;                    //���x��
		SoundSource* m_bgm = nullptr;                  //BGM
		Fade* m_fade = nullptr;                 //�t�F�[�h
		Player* m_player = nullptr;                         //�v���C���[
		EffectList* m_effectlist = nullptr;           //�G�t�F�N�g���X�g
		SoundList* m_soundlist = nullptr;            //�T�E���h���X�g
		SkyCube* m_sky = nullptr;                  //��
		int              m_skyCubeType = enSkyCubeType_Sky;//��̃^�C�v
	};
}