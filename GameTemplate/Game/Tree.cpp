#include "stdafx.h"
#include "Tree.h"
namespace App {
	Tree::Tree() {}
	Tree::~Tree() {}

	bool Tree::Start()
	{
		//���f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/bg/Tree.tkm", false, false);
		//���W�A��]�A�傫����ݒ肷��B
		SetupTRS();

		return true;
	}
	void Tree::Update()
	{
		//���f���̍X�V�B
		m_modelRender.Update();
	}
	void Tree::Render(RenderContext& rc)
	{
		//���f����`�悷��B
		m_modelRender.Draw(rc);
	}
}