#include "stdafx.h"
#include "IActor.h"

void IActor::SetupTRS()
{
	//���W��ݒ肷��B
	m_modelRender.SetPosition(m_position);
	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_modelRender.SetScale(m_scale);
	//���f�����X�V����B
	m_modelRender.Update();
}