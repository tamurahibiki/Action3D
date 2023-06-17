#include "stdafx.h"
#include "Wood_Road.h"
namespace App {
	Wood_Road::Wood_Road() {}
	Wood_Road::~Wood_Road() {}
	bool Wood_Road::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Wood_Road.tkm", true);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Wood_Road::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void Wood_Road::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}