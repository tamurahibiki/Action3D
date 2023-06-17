#include "stdafx.h"
#include "Flower.h"
namespace
{
	const int SCALEMULTIPLICATION = 4; //乗算する大きさ
}
namespace App {
	Flower::Flower() {}
	Flower::~Flower() {}

	bool Flower::Start()
	{
		//アニメーションを読み込む。
		m_animClips[enAnimationClip_Idle].Load("Assets/animData/Flower_Idle.tka");
		m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Flower.tkm", false, m_animClips, enAnimationCilp_Num);
		//座標、回転、大きさを設定する。
		m_scale *= SCALEMULTIPLICATION;
		SetupTRS();

		return true;
	}
	void Flower::Update()
	{
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.0f);
		//待機アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 1.0f);
		//モデルの更新。
		m_modelRender.Update();
	}
	void Flower::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}