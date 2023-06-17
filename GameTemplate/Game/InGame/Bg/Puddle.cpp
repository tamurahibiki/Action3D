#include "stdafx.h"
#include "Puddle.h"
namespace App {
	Puddle::Puddle() {}
	Puddle::~Puddle() {}

	bool Puddle::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Puddle.tkm", true);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Puddle::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void Puddle::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}