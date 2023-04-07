#pragma once
#include"IBgActor.h"
/// <summary>
/// 砲弾クラス
/// </summary>
class Shell :public IBgActor
{
public:
	Shell();
	~Shell();
	bool Start();
	void Update();
	//当たり判定。
	void Collision();
	//衝突後の処理。
	void CollisionEstablishment();
	void Render(RenderContext& rc);
	
private:
	/// <summary>
	/// 倒れる効果音を再生する。
	/// </summary>
	/// <returns>倒れる効果音を再生するならtrue。</returns>
	bool                    DownSound = true;
	Vector3					m_moveSpeed;						//移動速度。
	float					m_timer = 0.0f;						//タイマー。
};