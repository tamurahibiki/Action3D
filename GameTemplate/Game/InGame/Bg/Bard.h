#pragma once
#include "InGame/Bg/IBgActor.h"
/// <summary>
/// 鳥クラス
/// </summary>
namespace App {
	class Bard :public IBgActor
	{
	public:
		//鳥のステート
		enum EnBardState {
			enBardState_Idle,             //待機ステート
			enBardState_Move              //移動ステート
		};
	public:
		Bard();
		~Bard();
		bool Start();
		void Update();
		//移動処理
		void Move();
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
		/// 移動ステートの遷移処理。
		/// </summary>
		void ProcessMoveStateTransition();
		//鳥のアニメーションクリップ
		enum EnAnimationClip {
			enAnimationClip_Idle,  //待機
			enAnimationClip_Move,  //移動
			enAnimationCilp_Num,
		};

		Vector3				  m_moveSpeed;                      //移動速度
		AnimationClip         m_animClips[enAnimationCilp_Num]; //アニメーションクリップ
		EnBardState		      m_bardState = enBardState_Idle;   //鳥のステート
		float			      m_disappearTime = 0.0f;           //鳥が消える時間
		/// <summary>
		/// 羽ばたく効果音を再生する。
		/// </summary>
		/// <returns>羽ばたく効果音を再生するならtrue。</returns>
		bool                  m_moveSound = true;
	};
}