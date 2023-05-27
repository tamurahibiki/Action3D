#pragma once
#include "level3D/Level.h"
#include "time/GameTime.h"

/// <summary>
/// ゲームクラス
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
		//プレイヤーのゴール、死亡後の処理
		void Retry();
		//プレイヤーの位置情報が必要なオブジェクトを削除する。
		void DeleteModel();
		//体力
		int    HP = 5;
		/// <summary>
		/// 中間地点に到達しているか。
		/// </summary>
		/// <returns>中間地点に到達しているならtrue。</returns>
		bool   Try = false;
		/// <summary>
		///プレイヤーが生まれた直後か。
		/// </summary>
		/// <returns>プレイヤーが生まれた直後ならtrue。</returns>
		bool   PlayerSpawn = true;
		float  m_gameTime = 300.0f;//制限時間

	private:
		/// <summary>
		///フェードアウト中か。
		/// </summary>
		/// <returns>フェードアウト中ならtrue。</returns>
		bool             m_isWaitFadeout = false;
		ModelRender      m_modelRender;                    //モデルレンダー
		GameCamera* m_gameCamera;                     //ゲームカメラ
		Level            m_levelRender;                    //レベル
		SoundSource* m_bgm = nullptr;                  //BGM
		Fade* m_fade = nullptr;                 //フェード
		Player* m_player = nullptr;                         //プレイヤー
		EffectList* m_effectlist = nullptr;           //エフェクトリスト
		SoundList* m_soundlist = nullptr;            //サウンドリスト
		SkyCube* m_sky = nullptr;                  //空
		int              m_skyCubeType = enSkyCubeType_Sky;//空のタイプ
	};
}