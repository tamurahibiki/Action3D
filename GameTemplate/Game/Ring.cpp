#include "stdafx.h"
#include "Ring.h"

namespace
{
	//モデルを回転する加算速度。
	const float ADDROTATION = 12.0f;
}
namespace App {
	Ring::Ring() {}
	Ring::~Ring() {}

	bool Ring::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Ring.tkm", true, true);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Ring::Update()
	{
		//常にモデルがZ軸方向に回転するようにする。
		m_rotation.AddRotationDegZ(ADDROTATION);
		//回転を設定する。
		m_modelRender.SetRotation(m_rotation);
		//モデルの更新。
		m_modelRender.Update();
	}
	void Ring::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}