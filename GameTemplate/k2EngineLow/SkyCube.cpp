#include "k2EngineLowPreCompile.h"
#include "SkyCube.h"

namespace nsK2EngineLow {

	SkyCube::SkyCube()
	{
		m_textureFilePaths[enSkyCubeType_Sky] = L"Assets/modelData/preset/skyCubeMapDay_Toon.dds";
	}

	SkyCube::~SkyCube()
	{

	}

	bool SkyCube::Start()
	{
		ModelInitData initData;
		//tkm�t�@�C���̃t�@�C���p�X���w�肷��B
		initData.m_tkmFilePath = "Assets/modelData/preset/sky.tkm";
		//�V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��B
		initData.m_fxFilePath = "Assets/shader/SkyCubeMap.fx";
		initData.m_vsEntryPointFunc = "VSMain";
		initData.m_psEntryPointFunc = "PSMain";

		for (int i = 0; i < enSkyCubeType_Num; i++) {
			m_texture[i].InitFromDDSFile(m_textureFilePaths[i]);
		}

		initData.m_expandShaderResoruceView[0] = &m_texture[m_type];
		initData.m_expandConstantBuffer = &m_luminance;
		initData.m_expandConstantBufferSize = sizeof(m_luminance);
		
		m_modelRender.Init(initData);
		m_modelRender.UpdateWorldMatrix(m_position, g_quatIdentity, m_scale);
		return true;
	}

	void SkyCube::Update()
	{
		if (m_isDirty)
		{
			//m_modelRender.SetTRS(m_position, g_quatIdentity, m_scale);
			m_modelRender.UpdateWorldMatrix(m_position, g_quatIdentity, m_scale);
			m_isDirty = false;
		}
	}

	void SkyCube::Render(RenderContext& rc)
	{
		m_modelRender.Draw(rc);
	}
}