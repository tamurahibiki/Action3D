#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {
	ModelRender::ModelRender()
	{

	}
	ModelRender::~ModelRender()
	{

	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンのデータを読み込み。
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init
			(   m_skeleton,
				m_animationClips,
				m_numAnimationClips);
		}
	}

	void ModelRender::Init( const char* filePath,
		bool shadowRecieve,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool isShadowReciever,
		int maxInstance
	)
	{
		ModelInitData initData;

		//シェーダーファイルのファイルパス。
		initData.m_fxFilePath = "Assets/shader/model.fx";

		//モデルの定数バッファ用の情報をモデルの初期化情報として渡す。
		initData.m_expandConstantBuffer = &g_renderingEngine.GetModelRenderCB();
		initData.m_expandConstantBufferSize = sizeof(g_renderingEngine.GetModelRenderCB());
		if (animationClips == nullptr)
		{
			//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
			initData.m_vsEntryPointFunc = "VSMain";
		}
		else
		{
			//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
			initData.m_vsSkinEntryPointFunc = "VSSkinMain";
			InitSkeleton(filePath);
			//スケルトンを指定する。
			initData.m_skeleton = &m_skeleton;
			InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		}
		if (shadowRecieve) {
			initData.m_psEntryPointFunc = "PSMainShadowReciever";
			m_isShadowCaster = false;
		}
		else
		{
			m_isShadowCaster = true;
		}
		
		initData.m_expandShaderResoruceView[0] = &g_renderingEngine.GetShadowMap();
		initData.m_expandShaderResoruceView[1] = &g_renderingEngine.GetGBufferDepth();
		initData.m_expandShaderResoruceView[2] = &g_renderingEngine.GetGBufferNormal();
		initData.m_expandShaderResoruceView[3] = &g_renderingEngine.GetGBufferMetallicSmooth();
		initData.m_expandShaderResoruceView[4] = &g_ssr.GetResultTexture();

		initData.m_tkmFilePath = filePath;
		
		m_enFbxUpAxis = enModelUpAxis;
		initData.m_modelUpAxis = m_enFbxUpAxis;
		m_model.Init(initData);
		InitShadowModel(filePath, m_enFbxUpAxis);
		InitGBuffer(filePath, m_enFbxUpAxis);
		InitSsr(filePath, m_enFbxUpAxis);
	}

	void ModelRender::UpdateInstancingData(int instanceNo, const Vector3& pos, const Quaternion& rot, const Vector3& scale)
	{
		K2_ASSERT(m_numInstance < m_maxInstance, "インスタンスの数が多すぎです。");
		if (!m_isEnableInstancingDraw) {
			return;
		}
		auto wlorldMatrix = m_zprepassModel.CalcWorldMatrix(pos, rot, scale);

		
		m_worldMatrixArray[m_numInstance] = wlorldMatrix;
		if (m_numInstance == 0) {
			
			m_skeleton.Update(g_matIdentity);
			
			m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
		}
		m_numInstance++;
	}

	void ModelRender::Update()
	{
		
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_shadowmodel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_gbuffer.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_ssrmodel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		if (m_skeleton.IsInited()) {
			//スケルトンを更新。
			m_skeleton.Update(m_model.GetWorldMatrix());
		}

		//アニメーションを進める。
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		m_model.Draw(rc);
		
		//sphereModel.Draw(rc);

		g_renderingEngine.AddRenderObject(this);
	}
	void ModelRender::RemoveInstance(int instanceNo)
	{
		int matrixIndex = m_instanceNoToWorldMatrixArrayIndexTable[instanceNo];

		m_worldMatrixArray[matrixIndex] = g_matZero;
	}

	void ModelRender::InitShadowModel(const char* tkmFilePath, EnModelUpAxis modelUpAxis)
	{
		ModelInitData ShadowModelInitData;

		ShadowModelInitData.m_fxFilePath = "Assets/shader/DrawShadowMap.fx";
		ShadowModelInitData.m_tkmFilePath = tkmFilePath;
		if (m_animationClips != nullptr) {
			ShadowModelInitData.m_skeleton = &m_skeleton;
			ShadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else
		{
			ShadowModelInitData.m_vsSkinEntryPointFunc = "VSMain";
		}
		ShadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT,
		ShadowModelInitData.m_modelUpAxis = modelUpAxis;
		m_shadowmodel.Init(ShadowModelInitData);
	}
	
	void ModelRender::OnRenderShadowMap(RenderContext& rc,const Matrix& lvpMatrix)
	{
		if (m_isShadowCaster)
		{
			m_shadowmodel.Draw(
				rc,
				g_matIdentity,
				lvpMatrix);
		}
	}
	void ModelRender::InitGBuffer(const char* tkmFilePath, EnModelUpAxis modelUpAxis)
	{
		ModelInitData GBufferInitData;
		GBufferInitData.m_fxFilePath = "Assets/shader/model.fx";
		GBufferInitData.m_modelUpAxis = modelUpAxis;
		GBufferInitData.m_tkmFilePath = tkmFilePath;
        
		GBufferInitData.m_psEntryPointFunc = "PSMainColor";

		GBufferInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;
		GBufferInitData.m_colorBufferFormat[1] = DXGI_FORMAT_R8G8B8A8_UNORM;
		GBufferInitData.m_colorBufferFormat[2] = DXGI_FORMAT_R8G8B8A8_UNORM;

		m_gbuffer.Init(GBufferInitData);
	}
	void ModelRender::OnRenderToGBuffer(RenderContext& rc)
	{
		m_gbuffer.Draw(rc);
	}
	void ModelRender::InitSsr(const char* tkmFilePath, EnModelUpAxis modelUpAxis)
	{
		ModelInitData SsrInitData;
		SsrInitData.m_fxFilePath = "Assets/shader/ssr.fx";
		SsrInitData.m_tkmFilePath = tkmFilePath;

		SsrInitData.m_psEntryPointFunc = "PSFinal";

		SsrInitData.m_colorBufferFormat[0] = 
		g_postEffect.mainRenderTarget.GetColorBufferFormat(),
		SsrInitData.m_modelUpAxis = modelUpAxis;

		m_ssrmodel.Init(SsrInitData);
	}
	void ModelRender::OnRenderSsr(RenderContext& rc)
	{
		m_ssrmodel.Draw(rc);
	}
}