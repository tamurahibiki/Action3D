#include "stdafx.h"
#include "IEnemy.h"
namespace App {
	void IEnemy::EnemyRotation()
	{
		if (fabsf(m_moveSpeed.x) < 0.001f
			&& fabsf(m_moveSpeed.z) < 0.001f) {
			//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
			//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
			return;
		}
		//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
		//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
		//atan2���g�p���āA�p�x�����߂Ă���B
		//���ꂪ��]�p�x�ɂȂ�B
		float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
		//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
		//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
		m_rotation.SetRotationY(-angle);
		//��]��ݒ肷��B
		m_modelRender.SetRotation(m_rotation);
		//�v���C���[�̑O�x�N�g�����v�Z����B
		m_forward = Vector3::AxisZ;
		m_rotation.Apply(m_forward);
	}
}