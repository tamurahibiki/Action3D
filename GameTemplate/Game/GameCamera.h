#pragma once

/// <summary>
/// ゲームカメラクラス
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
		//通常カメラ設定
		void DefaultUpdatePositionAndTarget();
		//ゴールカメラ設定
		void GoalUpdatePositionAndTarget();
		//通常のカメラアングル
		void DefaultCamera();
		//奥行きが分かるカメラアングル      
		void ForWardCamera();
		//大砲発射前のカメラアングル
		void FortStayCamera();
		//大砲移動時上昇のカメラアングル
		void FortMoveUpCamera();
		//大砲移動時降下のカメラアングル
		void FortMoveFallCamera();
		//ゴール時のカメラアングル
		void GoalCamera();
		//死亡時のカメラアングル
		void DeadCamera();

		Vector3               m_toCameraPos = Vector3::One;//座標
		Quaternion            m_toCamerarot;               //回転
		Player* m_player;                    //プレイヤー                            
		GoalPoint* m_goal;                      //ゴール
		Game* m_game;                      //ゲーム
	};
}