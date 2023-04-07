#pragma once
#include "IBgActor.h"
class Player_Head;
/// <summary>
/// 大砲クラス
/// </summary>
class Fort :public IBgActor
{
	//大砲のステート
	enum EnFortState {
		enFortState_Idle,             //待機ステート
		enFortState_Move,             //作動ステート
	};
public:
	Fort();
	~Fort();
	bool Start();
	void Update();
	void ManageState();  //ステート処理
	void PlayAnimation();//アニメーション処理
	void MakeHead();      //プレイヤーの頭を生成する。
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
	/// 作動ステートの遷移処理。
	/// </summary>
	void ProcessMoveStateTransition();
	//アニメーションイベント用の関数
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	//大砲のアニメーションクリップ
	enum EnAnimationClip {
		enAnimationClip_Idle,//待機
		enAnimationClip_Move,//作動
		enAnimationCilp_Num,
	};

	AnimationClip       m_animClips[enAnimationCilp_Num];//アニメーションクリップ
	EnFortState		    m_fortState = enFortState_Idle;  //大砲のステート
	Player_Head*         m_head = nullptr;                 //プレイヤーの頭
	/// <summary>
	/// プレイヤーの頭を描画する。
	/// </summary>
	/// <returns>プレイヤーの頭を描画するならtrue。</returns>
	bool Head = true;
};

