#include "stdafx.h"
#include "Fade.h"

namespace
{
	const float ZERO = 0.0f;
	const float ONE = 1.0f;
	const Vector3	SCALE     = Vector3(2.16f, 2.16f, 1.0f); //大きさ
	const Vector3	POSITIOIN = Vector3(-140.0f, 10.0, 0.0f);//座標
}

Fade::Fade(){}
Fade::~Fade(){}
bool Fade::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/fade.dds", 1024, 512);
	//座標を設定する。
	m_spriteRender.SetPosition(POSITIOIN);
	//大きさを設定する。
	m_spriteRender.SetScale(SCALE);
	//画像を更新する。
	m_spriteRender.Update();
	return true;
}
void Fade::Update()
{
	switch (m_state) {
	//フェードインステートの時。
	case enState_FadeIn:
		//透明にする。
		m_currentAlpha -= ONE * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha <= ZERO) {
			m_currentAlpha = ZERO;
			m_state = enState_Idle;
		}
		break;
	//フェードアウトステートの時。
	case enState_FadeOut:
		//透明にしない。
		m_currentAlpha += ONE * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha >= ONE) {
			m_currentAlpha = ONE;
			m_state = enState_Idle;
		}
		break;
	//待機ステートの時。
	case enState_Idle:
		break;
	}
}
void Fade::Render(RenderContext& rc)
{
	//画像の設定
	if (m_currentAlpha > ZERO) {
		m_spriteRender.SetMulColor({ ONE, ONE, ONE, m_currentAlpha });
		//画像を描画する。
		m_spriteRender.Draw(rc);
	}
}