#include "stdafx.h"
#include "Pipe.h"

namespace App {
	Pipe::Pipe() {}
	Pipe::~Pipe() {}
	bool Pipe::Start()
	{
		//モデルを読み込む。
		m_modelRender.Init("Assets/modelData/bg/Pipe.tkm", true, false);
		//座標、回転、大きさを設定する。
		SetupTRS();

		return true;
	}
	void Pipe::Update()
	{
		//モデルの更新。
		m_modelRender.Update();
	}
	void Pipe::Render(RenderContext& rc)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
}