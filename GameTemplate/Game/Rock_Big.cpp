#include "stdafx.h"
#include "Rock_Big.h"

Rock_Big::Rock_Big() {}
Rock_Big::~Rock_Big() {}

bool Rock_Big::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/bg/Rock_Big.tkm", false);
	//座標、回転、大きさを設定する。
	SetupTRS();
	
	return true;
}
void Rock_Big::Update()
{
	//モデルの更新。
	m_modelRender.Update();
}
void Rock_Big::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}