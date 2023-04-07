#include "stdafx.h"
#include "WoodenBox.h"

WoodenBox::WoodenBox() {}
WoodenBox::~WoodenBox(){}

bool WoodenBox::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/gimmick/WoodenBox.tkm", false);
	//座標、回転、大きさを設定する。
	SetupTRS();
	
	return true;
}
void WoodenBox::Update()
{
	//モデルの更新。
	m_modelRender.Update();
}
void WoodenBox::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}