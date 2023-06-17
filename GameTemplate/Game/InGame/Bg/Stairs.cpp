#include "stdafx.h"
#include "Stairs.h"
namespace App {
	Stairs::Stairs() {}
	Stairs::~Stairs() {}

	bool Stairs::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Stairs.tkm", true);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Stairs::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void Stairs::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}