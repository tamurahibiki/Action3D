#include "stdafx.h"
#include "Title.h"
#include "InGame/Game.h"
#include "Fade.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SoundList.h"
namespace App {
	Title::Title() {}
	Title::~Title()
	{
		//BGMを削除する。
		DeleteGO(m_bgm);
	}
	bool Title::Start()
	{
		//画像を読み込む。
		m_spriteRender.Init("Assets/sprite/title.DDS", 1920, 1040);

		m_pressButton.Init("Assets/sprite/button.DDS", 1293, 646);
		m_pressButton.SetPosition(Vector3(0.0f, -150.0f, 0.0f));

		m_soundlist = FindGO<SoundList>("soundlist");
		//BGM。
		m_bgm = NewGO<SoundSource>(0);
		m_bgm->Init(m_soundlist->TITLEBGM);
		m_bgm->Play(true);
		m_bgm->SetVolume(0.2f);

		m_fade = FindGO<Fade>("fade");
		m_fade->StartFadeIn();
		return true;
	}
	void Title::Update()
	{
		if (m_isWaitFadeout) {
			if (!m_fade->IsFade()) {
				NewGO<Game>(0, "game");
				//自身を削除する。
				DeleteGO(this);
			}
		}
		else {
			//Aボタンを押したら。
			if (g_pad[0]->IsTrigger(enButtonA)) {
				//効果音を再生する。
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(m_soundlist->TITLEA);
				se->Play(false);
				se->SetVolume(0.5f);
				m_isWaitFadeout = true;
				m_fade->StartFadeOut();
			}
		}
		//α値を変化させる。
		if (m_isWaitFadeout)
		{
			m_alpha += g_gameTime->GetFrameDeltaTime() * 1.5f;
		}
		else
		{
			m_alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
		}
		m_pressButton.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));
		//画像の更新。
		m_spriteRender.Update();
		m_pressButton.Update();
	}
	void Title::Render(RenderContext& rc)
	{
		//画像の描画。
		m_spriteRender.Draw(rc);
		m_pressButton.Draw(rc);
	}
}