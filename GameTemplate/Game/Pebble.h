#pragma once
#include "IBgActor.h"
/// <summary>
/// 小石クラス
/// </summary>
class Pebble : public IBgActor
{
public:
	//小石のステート
	enum EnPebbleState
	{
		enPebbleState_Idle,//待機ステート
		enPebbleState_Move //移動ステート
	};
public:
	Pebble();
	~Pebble();
	bool Start();
	void Update();
	void Move();         //移動処理
	void PlayAnimation();//アニメーション処理
	void ManageState();  //ステート処理
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
     //小石のアニメーション
	enum EnAnimationClip {		
		enAnimationClip_Idle,//待機
		enAnimationClip_Move,//移動
		enAnimationClip_Num,
	};

	Vector3		    m_moveSpeed;						  //移動速度。
	AnimationClip	m_animationClips[enAnimationClip_Num];//アニメーションクリップ
	Quaternion      m_playerrotation;                     //プレイヤーの回転
	EnPebbleState   m_pebbleState = enPebbleState_Idle;   //小石のステート
	/// <summary>
	/// 小石の移動方向を決める。
	/// </summary>
	/// <returns>小石の移動方向を決められるならtrue。</returns>
	bool PebbleRot = true;
};