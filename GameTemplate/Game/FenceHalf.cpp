#include "stdafx.h"
#include "FenceHalf.h"
namespace App {
	FenceHalf::FenceHalf() {}
	FenceHalf::~FenceHalf() {}

	bool FenceHalf::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/FenceHalf.tkm", true,false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void FenceHalf::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void FenceHalf::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}