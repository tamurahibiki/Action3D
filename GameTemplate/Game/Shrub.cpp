#include "stdafx.h"
#include "Shrub.h"

Shrub::Shrub() {}
Shrub::~Shrub() {}

bool Shrub::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/bg/Shrub.tkm", true);
	//座標、回転、大きさを設定する。
	SetupTRS();

	return true;
}
void Shrub::Update()
{
	//モデルの更新。
	m_modelRender.Update();
}
void Shrub::Render(RenderContext& rc)
{
	//モデルを更新。
	m_modelRender.Draw(rc);
}