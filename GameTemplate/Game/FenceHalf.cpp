#include "stdafx.h"
#include "FenceHalf.h"
namespace App {
	FenceHalf::FenceHalf() {}
	FenceHalf::~FenceHalf() {}

	bool FenceHalf::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/FenceHalf.tkm", true,false);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void FenceHalf::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void FenceHalf::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}