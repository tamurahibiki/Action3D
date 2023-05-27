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
		//�X�P���g���̃f�[�^��ǂݍ��݁B
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
	//	// step-1 �������̃��f����������
	//	transModelInitData.m_tkmFilePath = filePath;
	//	transModelInitData.m_fxFilePath = "Assets/shader/model.fx";
	//	// ���������f���̓��f����`���Ƃ��Ƀ��C�e�B���O���s���̂ŁA���C�g�̏���n���B
	//	transModelInitData.m_expandConstantBuffer = &g_Light.GetLight();
	//	transModelInitData.m_expandConstantBufferSize = sizeof(g_Light.GetLight());
	//	// �s�N�Z���V�F�[�_�̃G���g���[�|�C���g���s�������f���Ƃ͈قȂ�B
	//	// �s�������f����PSMain�A���������f����PSMainTrans���g�p����B
	//	// �s�N�Z���V�F�[�_�̎����͌�Ŋm�F�B
 //       //transModelInitData.m_psEntryPointFunc = "PSMainTrans";

	//	//�y�d�v�z�����������B
	//	transModelInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//	// �������̋��̃��f�����������B
	//	sphereModel.Init(transModelInitData);
	//}


	//void ModelRender::InitForwardRendering(ModelInitData& initData)
	//{
	//	//�C���X�^���V���O�`��p�̃f�[�^���������B
	//	InitInstancingDraw(1);
	//	InitSkeleton(initData.m_tkmFilePath);

	//	// todo �A�j���[�V�����ςݒ��_�o�b�t�@�̌v�Z�������������B
	//	//InitComputeAnimatoinVertexBuffer(initData.m_tkmFilePath, initData.m_modelUpAxis);

	//	initData.m_colorBufferFormat[0] = DXGI_FORMAT_R16G16B16A16_FLOAT;
	//	//�쐬�����������f�[�^�����ƂɃ��f��������������B
	//	m_forwardRenderModel.Init(initData);
	//	//ZPrepass�`��p�̃��f�����������B
	//	//InitModelOnZprepass(*g_renderingEngine, initData.m_tkmFilePath, initData.m_modelUpAxis);
	//	//�V���h�E�}�b�v�`��p�̃��f�����������B
	//	//Init(*g_renderingEngine, initData.m_tkmFilePath, initData.m_modelUpAxis, false);
	//	// �􉽊w�f�[�^���������B
	//	//InitGeometryDatas(1);
	//	// ���C�g�����[���h�ɒǉ��B
	//	// g_renderingEngine->AddModelToRaytracingWorld(m_forwardRenderModel);
	//	// m_addRaytracingWorldModel = &m_forwardRenderModel;
	//	// �e�탏�[���h�s����X�V����B
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
	//		// �C���X�^���V���O�`����s���̂ŁA
	//		// ����p�̃f�[�^���\�z����B
	//		// ���[���h�s��̔z��̃��������m�ۂ���B
	//		m_worldMatrixArray = std::make_unique<Matrix[]>(m_maxInstance);
	//		// ���[���h�s���GPU�ɓ]�����邽�߂̃X�g���N�`���[�h�o�b�t�@���m�ہB
	//		m_worldMatrixArraySB.Init(
	//			sizeof(Matrix),
	//			m_maxInstance,
	//			nullptr
	//		);
	//		m_isEnableInstancingDraw = true;
	//		// �C���X�^���X�ԍ����烏�[���h�s��̔z��̃C���f�b�N�X�ɕϊ�����e�[�u��������������B
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

		//�V�F�[�_�[�t�@�C���̃t�@�C���p�X�B
		initData.m_fxFilePath = "Assets/shader/model.fx";

		//���f���̒萔�o�b�t�@�p�̏������f���̏��������Ƃ��ēn���B
		initData.m_expandConstantBuffer = &g_renderingEngine.GetModelRenderCB();
		initData.m_expandConstantBufferSize = sizeof(g_renderingEngine.GetModelRenderCB());
		if (animationClips == nullptr)
		{
			//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
			initData.m_vsEntryPointFunc = "VSMain";
		}
		else
		{
			//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
			initData.m_vsSkinEntryPointFunc = "VSSkinMain";
			InitSkeleton(filePath);
			//�X�P���g�����w�肷��B
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
		K2_ASSERT(m_numInstance < m_maxInstance, "�C���X�^���X�̐����������ł��B");
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
			//�X�P���g�����X�V�B
			m_skeleton.Update(m_model.GetWorldMatrix());
		}

		//�A�j���[�V������i�߂�B
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