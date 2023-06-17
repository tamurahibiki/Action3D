#include "stdafx.h"
#include "Signboard.h"
namespace App {
	Signboard::Signboard() {}
	Signboard::~Signboard() {}

	bool Signboard::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Signboard.tkm", false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		//当たり判定を作成する。
		m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
			m_modelRender.GetModel().GetWorldMatrix());
		return true;
	}
	void Signboard::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void Signboard::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}