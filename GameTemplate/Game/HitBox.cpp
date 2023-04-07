#include "stdafx.h"
#include "HitBox.h"

HitBox::HitBox() {}
HitBox::~HitBox() {}

bool HitBox::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/Box.tkm", true);
	//座標、回転、大きさを設定する。
	SetupTRS();
	
	//当たり判定を作成する。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix());
	return true;
}
void HitBox::Update()
{
	//モデルの更新。
	m_modelRender.Update();
}