#include "stdafx.h"
#include "Tree.h"
namespace App {
	Tree::Tree() {}
	Tree::~Tree() {}

	bool Tree::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Tree.tkm", false, false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Tree::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void Tree::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}