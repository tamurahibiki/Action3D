#pragma once
#include "IEnemy.h"

/// <summary>
/// 飛んでいるエネミークラス
/// </summary>
namespace App {
	class Enemy_Yellow :public IEnemy
	{
		//飛んでいるエネミーのステート
		enum EnEnemy_BlueState {
			enEnemyState_Idle,     //待機	
			enEnemyState_Discovery,//発見
			enEnemyState_Move,     //移動
			enEnemyState_Down      //死亡
		};
	public:
		Enemy_Yellow();
		~Enemy_Yellow();
		bool Start();
		void Update();
		//回転処理
		void Rotation();
		//追従処理
		void Chase();
		//当たり判定
		void Collision();
		//アニメーション処理
		void PlayAnimation();
		//ステート処理
		void ManageState();
		void Render(RenderContext& rc);

	private:
		/// <summary>
		/// プレイヤーを探索する。
		/// </summary>
		/// <returns>プレイヤーが見つかったらtrue。</returns>
		const bool SearchPlayer() const;
		/// <summary>
		/// 共通のステート遷移処理。
		/// </summary>
		void ProcessCommonStateTransition();
		/// <summary>
		/// 発見ステート遷移処理。
		/// </summary>
		void ProcessDiscoveryStateTransition();
		/// <summary>
		/// 死亡ステート遷移処理。
		/// </summary>
		void ProcessDownStateTransition();
		//アニメーションイベント用の関数
		void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
		//飛んでいるエネミーのアニメーションクリップ
		enum EnAnimationClip {
			enAnimationClip_Idle,     //待機
			enAnimationClip_Discovery,//発見
			enAnimationClip_Move,     //移動
			enAnimationClip_Down,     //死亡
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//アニメーションクリップ
		EnEnemy_BlueState	m_EnemyState = enEnemyState_Idle;//飛んでいるエネミーのステート
	};
}