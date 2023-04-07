#include "stdafx.h"
#include "Player_Head.h"

namespace
{
	const float ROTADDITIONX = 60.0f;
	const float ROTADDITIONY = 90.0f;
	const float SCALEMULTIPLICATION = 0.5; //乗算する大きさ
}

Player_Head::Player_Head() {}
Player_Head::~Player_Head() {}

bool Player_Head::Start()
{
	//アニメーションを読み込む。
	m_animClips[enAnimationClip_Idle].Load("Assets/animData/Player_Head.tka");
	m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/player/Player_Fort.tkm", false, m_animClips, enAnimationCilp_Num);
	//座標を設定する。
	m_modelRender.SetPosition(m_position);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);
	m_rotation.y += ROTADDITIONY;
	m_rotation.x += ROTADDITIONX;
	//大きさを設定する。
	m_modelRender.SetScale(m_scale* SCALEMULTIPLICATION);
	//モデルを更新する。
	m_modelRender.Update();
	return true;
}
void Player_Head::Update()
{
	//アニメーションの再生速度。
	m_modelRender.SetAnimationSpeed(1.0f);
	//待機アニメーションを再生。
	m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.8f);
	//モデルの更新処理。
	m_modelRender.Update();
}
void Player_Head::Render(RenderContext& rc)
{
	//モデルの描画。
	m_modelRender.Draw(rc);
}