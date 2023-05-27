#include "k2EngineLowPreCompile.h"
#include "ShadowMapRender.h"

namespace nsK2EngineLow {

	void ShadowMapRender::Init()
	{
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		shadowMap.Create(
			4096,
			4096,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}
	void ShadowMapRender::Render(RenderContext& rc, Vector3 ligDirection, std::vector<IRenderer*>& renderObjects)
	{

		//カメラの位置を設定。これはライトの置。
		m_lightCamera.SetPosition({ g_camera3D->GetTarget().x,g_camera3D->GetTarget().y + 3000,g_camera3D->GetTarget().z });
		//カメラの注視点を設定。これがライトが照らしている場所。
		m_lightCamera.SetTarget(g_camera3D->GetTarget());
		//【注目】上方向を設定。今回はライトが真下を向いているので、X方向を上にしている。
		m_lightCamera.SetUp(1, 0, 0);

		//m_lightCamera.SetViewAngle(Math::DegToRad(10.0f));
		m_lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
		m_lightCamera.SetWidth(15000.0f);
		m_lightCamera.SetHeight(15000.0f);
		m_lightCamera.SetFar(10000.0f);
		//ライトビュープロジェクション行列を計算している。
		m_lightCamera.Update();


		rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
		rc.SetRenderTargetAndViewport(shadowMap);
		rc.ClearRenderTargetView(shadowMap);

		for (auto& model : renderObjects)
		{
			model->OnRenderShadowMap(rc, m_lightCamera.GetViewProjectionMatrix());

		}

		rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

	}
}