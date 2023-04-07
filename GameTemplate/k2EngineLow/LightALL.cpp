#include "k2EngineLowPreCompile.h"
#include "LightALL.h"

namespace nsK2EngineLow {
	LightALL g_Light;


	void LightALL::Init()
	{

//ディレクションライト
//ライトは左側から当たっている
		m_light.directionlight.dirDirection.x = 0.0f;
		m_light.directionlight.dirDirection.y = 0.0f;
		m_light.directionlight.dirDirection.z = -1.0f;
		m_light.directionlight.dirDirection.Normalize();
		// ライトのカラーは灰色
		m_light.directionlight.dirColor.x = 0.5f;
		m_light.directionlight.dirColor.y = 0.5f;
		m_light.directionlight.dirColor.z = 0.5f;


		//ポイントライト
		// ポイントライトの座標を設定する
		m_light.pointlight.ptPosition.x = 0.0f;
		m_light.pointlight.ptPosition.y = 50.0f;
		m_light.pointlight.ptPosition.z = 50.0f;
		// ポイントライトのカラーを設定する
		m_light.pointlight.ptColor.x = 0.0f;
		m_light.pointlight.ptColor.y = 0.0f;
		m_light.pointlight.ptColor.z = 0.0f;
		// ポイントライトの影響範囲を設定する
		m_light.pointlight.ptRange = 0.0f;

		m_light.spotlight.spPosition.x = 0.0f;
		m_light.spotlight.spPosition.y = 50.0f;
		m_light.spotlight.spPosition.z = 0.0f;
		//スポットライトのカラーを設定。R = 10、G = 10、B = 10にする。
		m_light.spotlight.spColor.x = 10.0f;
		m_light.spotlight.spColor.y = 10.0f;
		m_light.spotlight.spColor.z = 10.0f;
		
		//初期方向は斜め下にする。
		m_light.spotlight.spDirection.x = 1.0f;
		m_light.spotlight.spDirection.y = -1.0f;
		m_light.spotlight.spDirection.z = 1.0f;
		//方向データなので、大きさを１にする必要があるので正規化する。
		m_light.spotlight.spDirection.Normalize();
		//射出範囲
		m_light.spotlight.spRange = 10.0f;
		//射出角度は25度。
		m_light.spotlight.spAngle = Math::DegToRad(25.0f);

		
		SetAmbientLight({ 0.6f,0.6f,0.6f });

		m_light.eyePos = g_camera3D->GetPosition();
		
	}


	LightALL::~LightALL()
	{

	}

	void LightALL::Update()
	{
		// 視点の位置を設定する
		m_light.eyePos = g_camera3D->GetPosition();
		
		/*m_light.pointlight.ptPosition.x -= g_pad[0]->GetLStickXF();
		if (g_pad[0]->IsPress(enButtonB))
		{
			m_light.pointlight.ptPosition.y += g_pad[0]->GetLStickYF();
		}
		else
		{
			m_light.pointlight.ptPosition.z -= g_pad[0]->GetLStickYF();
		}*/

		//m_light.directionlight.dirColor.x += g_pad[0]->GetLStickXF() * 0.2f;
		//m_light.directionlight.dirColor.y += g_pad[0]->GetLStickXF() * 0.2f;
		//m_light.directionlight.dirColor.z += g_pad[0]->GetLStickXF() * 0.2f;
	}

}