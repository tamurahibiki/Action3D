#include "stdafx.h"
#include "Ground.h"

Ground::Ground() {}
Ground::~Ground() {}

bool Ground::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/bg/Graund.tkm",true);
	//座標、回転、大きさを設定する。
	SetupTRS();
	
	//当たり判定を作成する。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix());

	return true;
}
void Ground::Update()
{
	//モデルの更新。
	m_modelRender.Update();
}
void Ground::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}