#include "stdafx.h"
#include "system/system.h"
#include "InGame/Game.h"
#include "OutGame/Title.h"
#include "OutGame/Fade.h"
#include "SoundList.h"

// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	
	
	g_postEffect.Init();
	g_Light.Init();
	g_bloom.Init();
	g_renderingEngine.Init();
	g_ssr.Init();
	g_fxaa.Init();
	

	NewGO <App::SoundList> (0, "soundlist");
	NewGO<App::Title>(0,"title");
	NewGO<App::Fade>(0, "fade");
	 
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();
		g_k2EngineLow->BeginFrame();

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
		g_k2EngineLow->ExecuteUpdate();

		g_renderingEngine.Execute(renderContext);

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();

		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();
	}
	delete g_k2EngineLow;
	return 0;
}

