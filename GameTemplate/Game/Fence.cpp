#include "stdafx.h"
#include "Fence.h"

namespace App {
	Fence::Fence() {}
	Fence::~Fence() {}

	bool Fence::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Fence.tkm", true,false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Fence::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void Fence::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}