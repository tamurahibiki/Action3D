#include "k2EngineLowPreCompile.h"
#include "LightALL.h"

namespace nsK2EngineLow {
	LightALL g_Light;


	void LightALL::Init()
	{

//�f�B���N�V�������C�g
//���C�g�͍������瓖�����Ă���
		m_light.directionlight.dirDirection.x = 0.0f;
		m_light.directionlight.dirDirection.y = 0.0f;
		m_light.directionlight.dirDirection.z = -1.0f;
		m_light.directionlight.dirDirection.Normalize();
		// ���C�g�̃J���[�͊D�F
		m_light.directionlight.dirColor.x = 0.5f;
		m_light.directionlight.dirColor.y = 0.5f;
		m_light.directionlight.dirColor.z = 0.5f;


		//�|�C���g���C�g
		// �|�C���g���C�g�̍��W��ݒ肷��
		m_light.pointlight.ptPosition.x = 0.0f;
		m_light.pointlight.ptPosition.y = 50.0f;
		m_light.pointlight.ptPosition.z = 50.0f;
		// �|�C���g���C�g�̃J���[��ݒ肷��
		m_light.pointlight.ptColor.x = 0.0f;
		m_light.pointlight.ptColor.y = 0.0f;
		m_light.pointlight.ptColor.z = 0.0f;
		// �|�C���g���C�g�̉e���͈͂�ݒ肷��
		m_light.pointlight.ptRange = 0.0f;

		m_light.spotlight.spPosition.x = 0.0f;
		m_light.spotlight.spPosition.y = 50.0f;
		m_light.spotlight.spPosition.z = 0.0f;
		//�X�|�b�g���C�g�̃J���[��ݒ�BR = 10�AG = 10�AB = 10�ɂ���B
		m_light.spotlight.spColor.x = 10.0f;
		m_light.spotlight.spColor.y = 10.0f;
		m_light.spotlight.spColor.z = 10.0f;
		
		//���������͎΂߉��ɂ���B
		m_light.spotlight.spDirection.x = 1.0f;
		m_light.spotlight.spDirection.y = -1.0f;
		m_light.spotlight.spDirection.z = 1.0f;
		//�����f�[�^�Ȃ̂ŁA�傫�����P�ɂ���K�v������̂Ő��K������B
		m_light.spotlight.spDirection.Normalize();
		//�ˏo�͈�
		m_light.spotlight.spRange = 10.0f;
		//�ˏo�p�x��25�x�B
		m_light.spotlight.spAngle = Math::DegToRad(25.0f);

		
		SetAmbientLight({ 0.6f,0.6f,0.6f });

		m_light.eyePos = g_camera3D->GetPosition();
		
	}


	LightALL::~LightALL()
	{

	}

	void LightALL::Update()
	{
		// ���_�̈ʒu��ݒ肷��
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