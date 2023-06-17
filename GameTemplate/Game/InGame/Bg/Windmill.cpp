#include "stdafx.h"
#include "Windmill.h"
namespace App {
	Windmill::Windmill() {}
	Windmill::~Windmill() {}

	bool Windmill::Start()
	{
		//アニメーションを読み込む。
		m_animClips[enAnimationClip_Move].Load("Assets/animData/Windmill.tka");
		m_animClips[enAnimationClip_Move].SetLoopFlag(true);
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Windmill.tkm", false,m_animClips, enAnimationCilp_Num);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Windmill::Update()
	{
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.0f);
		//回転アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Move, 1.0f);
		//モデルの更新。
		m_modelRender.Update();
	}
	void Windmill::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}