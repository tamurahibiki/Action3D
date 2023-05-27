#pragma once
#include "IEnemy.h"

/// <summary>
/// 遠距離攻撃エネミークラス
/// </summary>
namespace App {
	class Enemy_Green :public IEnemy
	{
		//遠距離攻撃エネミーのステート
		enum EnEnemy_BlueState {
			enEnemyState_Idle,//待機
			enEnemyState_Attack,//攻撃
			enEnemyState_Down//死亡
		};
	public:
		Enemy_Green();
		~Enemy_Green();
		bool Start();
		void Update();
		//回転処理
		void Rotation();
		//攻撃(砲弾)の作成
		void MakeAttack();
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
		/// 待機ステート遷移処理。
		/// </summary>
		void ProcessIdleStateTransition();
		/// <summary>
		/// 攻撃ステート遷移処理。
		/// </summary>
		void ProcessAttackStateTransition();
		/// <summary>
		/// 死亡ステート遷移処理。
		/// </summary>
		void ProcessDownStateTransition();

		//アニメーションイベント用の関数
		void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
		//遠距離攻撃エネミーのアニメーションクリップ
		enum EnAnimationClip {
			enAnimationClip_Idle,//待機
			enAnimationClip_Attack,//攻撃
			enAnimationClip_Down,//死亡
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//アニメーションクリップ
		EnEnemy_BlueState	m_EnemyState = enEnemyState_Idle;//遠距離攻撃エネミーのステート
	};
}