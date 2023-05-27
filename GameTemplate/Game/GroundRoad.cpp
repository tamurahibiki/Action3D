#include "stdafx.h"
#include "GroundRoad.h"
namespace App {
	GroundRoad::GroundRoad() {}
	GroundRoad::~GroundRoad() {}

	bool GroundRoad::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/GroundRoad.tkm", true, false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void GroundRoad::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void GroundRoad::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}