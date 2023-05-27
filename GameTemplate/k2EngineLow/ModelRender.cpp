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
	//void ModelRender::InitModel(const char* filePath)
	//{
	//	// step-1 半透明のモデルを初期化
	//	transModelInitData.m_tkmFilePath = filePath;
	//	transModelInitData.m_fxFilePath = "Assets/shader/model.fx";
	//	// 半透明モデルはモデルを描くときにライティングを行うので、ライトの情報を渡す。
	//	transModelInitData.m_expandConstantBuffer = &g_Light.GetLight();
	//	transModelInitData.m_expandConstantBufferSize = sizeof(g_Light.GetLight());
	//	// ピクセルシェーダのエントリーポイントが不透明モデルとは異なる。
	//	// 不透明モデルはPSMain、半透明モデルはPSMainTransを使用する。
	//	// ピクセルシェーダの実装は後で確認。
 //       //transModelInitData.m_psEntryPointFunc = "PSMainTrans";

	//	//【重要】半透明合成。
	//	transModelInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//	// 半透明の球体モデルを初期化。
	//	sphereModel.Init(transModelInitData);
	//}


	//void ModelRender::InitForwardRendering(ModelInitData& initData)
	//{
	//	//インスタンシング描画用のデータを初期化。
	//	InitInstancingDraw(1);
	//	InitSkeleton(initData.m_tkmFilePath);

	//	// todo アニメーション済み頂点バッファの計算処理を初期化。
	//	//InitComputeAnimatoinVertexBuffer(initData.m_tkmFilePath, initData.m_modelUpAxis);

	//	initData.m_colorBufferFormat[0] = DXGI_FORMAT_R16G16B16A16_FLOAT;
	//	//作成した初期化データをもとにモデルを初期化する。
	//	m_forwardRenderModel.Init(initData);
	//	//ZPrepass描画用のモデルを初期化。
	//	//InitModelOnZprepass(*g_renderingEngine, initData.m_tkmFilePath, initData.m_modelUpAxis);
	//	//シャドウマップ描画用のモデルを初期化。
	//	//Init(*g_renderingEngine, initData.m_tkmFilePath, initData.m_modelUpAxis, false);
	//	// 幾何学データを初期化。
	//	//InitGeometryDatas(1);
	//	// レイトレワールドに追加。
	//	// g_renderingEngine->AddModelToRaytracingWorld(m_forwardRenderModel);
	//	// m_addRaytracingWorldModel = &m_forwardRenderModel;
	//	// 各種ワールド行列を更新する。
	//	//UpdateWorldMatrixInModes();
	//}

	/*void ModelRender::modelUpdate()
	{
		sphereModel.UpdateWorldMatrix(planePos, g_quatIdentity, g_vec3One);
	}*/
	
	//void ModelRender::InitInstancingDraw(int maxInstance)
	//{
	//	m_maxInstance = maxInstance;
	//	if (m_maxInstance > 1) {
	//		// インスタンシング描画を行うので、
	//		// それ用のデータを構築する。
	//		// ワールド行列の配列のメモリを確保する。
	//		m_worldMatrixArray = std::make_unique<Matrix[]>(m_maxInstance);
	//		// ワールド行列をGPUに転送するためのストラクチャードバッファを確保。
	//		m_worldMatrixArraySB.Init(
	//			sizeof(Matrix),
	//			m_maxInstance,
	//			nullptr
	//		);
	//		m_isEnableInstancingDraw = true;
	//		// インスタンス番号からワールド行列の配列のインデックスに変換するテーブルを初期化する。
	//		m_instanceNoToWorldMatrixArrayIndexTable = std::make_unique<int[]>(m_maxInstance);
	//		for (int instanceNo = 0; instanceNo < m_maxInstance; instanceNo++) {
	//			m_instanceNoToWorldMatrixArrayIndexTable[instanceNo] = instanceNo;
	//		}
	//	}
	//}

	void ModelRender::Init( const char* filePath,
		bool shadowRecieve,
		bool ssrRecieve,
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
		initData.m_tkmFilePath = filePath;
		
		m_enFbxUpAxis = enModelUpAxis;
		initData.m_modelUpAxis = m_enFbxUpAxis;
		m_model.Init(initData);
		InitShadowModel(filePath, m_enFbxUpAxis);
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

}