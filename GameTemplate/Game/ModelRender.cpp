#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {
	ModelRender::ModelRender()
	{
		
	}
	ModelRender::~ModelRender()
	{
		
	}
	
	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		int maxInstance
	)
	{
		ModelInitData initData;

		//シェーダーファイルのファイルパス。
		initData.m_fxFilePath = "Assets/shader/model.fx";

		//モデルの定数バッファ用の情報をモデルの初期化情報として渡す。
		initData.m_expandConstantBuffer = &g_renderingEngine.GetModelRenderCB();
		initData.m_expandConstantBufferSize = sizeof(g_renderingEngine.GetModelRenderCB());
		
		m_enFbxUpAxis = enModelUpAxis;
		initData.m_modelUpAxis = m_enFbxUpAxis;
		m_model.Init(initData);
	}
	

	void ModelRender::InitModel(const char* filePath)
	{
		m_modelInitData.m_tkmFilePath = filePath;
		m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		
		spheremodel.Init(m_modelInitData);
	}

	void ModelRender::modelUpdate()
	{
		spheremodel.UpdateWorldMatrix(m_position, g_quatIdentity, m_scale);
	}

	void ModelRender::Update()
	{
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	}

	void ModelRender::Draw(RenderContext&rc)
	{
		m_model, Draw(rc);
		spheremodel.Draw(rc);
		g_renderingEngine.AddRenderObject(this);
	}
	
}