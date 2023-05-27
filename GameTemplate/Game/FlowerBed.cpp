#include "stdafx.h"
#include "FlowerBed.h"

namespace
{
	const float SCALEMULTIPLICATION = 2.5;//乗算する大きさ
}
namespace App {
	FlowerBed::FlowerBed() {}
	FlowerBed::~FlowerBed() {}
	bool FlowerBed::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/FlowerBed.tkm", true,false );
		//座標、回転、大きさを設定する。
		m_scale *= SCALEMULTIPLICATION;
		SetupTRS();

		return true;
	}
	void FlowerBed::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void FlowerBed::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}