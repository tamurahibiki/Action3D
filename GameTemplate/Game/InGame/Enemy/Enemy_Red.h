#pragma once
#include "InGame/Enemy/IEnemy.h"

/// <summary>
/// 追いかけてくるエネミークラス
/// </summary>
namespace App {
	class Enemy_Red :public IEnemy
	{
		//追いかけてくるエネミーのステート
		enum EnEnemy_RedState {
			enEnemyState_Idle,//待機
			enEnemyState_Move,//移動
			enEnemyState_Down //死亡
		};
	public:
		Enemy_Red();
		~Enemy_Red();
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
		/// 待機ステート遷移処理。
		/// </summary>
		void ProcessIdleStateTransition();
		/// <summary>
		/// 死亡ステート遷移処理。
		/// </summary>
		void ProcessDownStateTransition();

		//アニメーションイベント用の関数
		void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
		//追いかけてくるエネミーのアニメーションクリップ
		enum EnAnimationClip {
			enAnimationClip_Idle,//待機
			enAnimationClip_Move,//移動
			enAnimationClip_Down,//死亡
			enAnimationCilp_Num,
		};
		AnimationClip       m_animClips[enAnimationCilp_Num];//アニメーションクリップ
		EnEnemy_RedState	m_EnemyState = enEnemyState_Move;//追いかけてくるエネミーのステート
	};
}