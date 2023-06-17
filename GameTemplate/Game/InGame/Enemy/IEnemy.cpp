#include "stdafx.h"
#include "IEnemy.h"
namespace App {
	void IEnemy::EnemyRotation()
	{
		if (fabsf(m_moveSpeed.x) < 0.001f
			&& fabsf(m_moveSpeed.z) < 0.001f) {
			//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
			//このフレームではキャラは移動していないので旋回する必要はない。
			return;
		}
		//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
		//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
		//atan2を使用して、角度を求めている。
		//これが回転角度になる。
		float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
		//atanが返してくる角度はラジアン単位なので
		//SetRotationDegではなくSetRotationを使用する。
		m_rotation.SetRotationY(-angle);
		//回転を設定する。
		m_modelRender.SetRotation(m_rotation);
		//プレイヤーの前ベクトルを計算する。
		m_forward = Vector3::AxisZ;
		m_rotation.Apply(m_forward);
	}
}