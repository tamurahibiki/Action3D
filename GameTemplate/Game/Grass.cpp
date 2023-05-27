#include "stdafx.h"
#include "Grass.h"

namespace
{
	const float SCALEMULTIPLICATION = 2.5;//乗算する大きさ
}
namespace App {
	Grass::Grass() {}
	Grass::~Grass() {}

	bool Grass::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Grass.tkm", true, false);
		//座標、回転、大きさを設定する。
		m_scale *= SCALEMULTIPLICATION;
		SetupTRS();

		return true;
	}
	void Grass::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void Grass::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}