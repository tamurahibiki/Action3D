#include "stdafx.h"
#include "IActor.h"

void IActor::SetupTRS()
{
	//座標を設定する。
	m_modelRender.SetPosition(m_position);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);
	//大きさを設定する。
	m_modelRender.SetScale(m_scale);
	//モデルを更新する。
	m_modelRender.Update();
}