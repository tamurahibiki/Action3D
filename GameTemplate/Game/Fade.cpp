#include "stdafx.h"
#include "Fade.h"

namespace
{
	const float ZERO = 0.0f;
	const float ONE = 1.0f;
	const Vector3	SCALE     = Vector3(2.16f, 2.16f, 1.0f); //�傫��
	const Vector3	POSITIOIN = Vector3(-140.0f, 10.0, 0.0f);//���W
}

Fade::Fade(){}
Fade::~Fade(){}
bool Fade::Start()
{
	//�摜��ǂݍ��ށB
	m_spriteRender.Init("Assets/sprite/fade.dds", 1024, 512);
	//���W��ݒ肷��B
	m_spriteRender.SetPosition(POSITIOIN);
	//�傫����ݒ肷��B
	m_spriteRender.SetScale(SCALE);
	//�摜���X�V����B
	m_spriteRender.Update();
	return true;
}
void Fade::Update()
{
	switch (m_state) {
	//�t�F�[�h�C���X�e�[�g�̎��B
	case enState_FadeIn:
		//�����ɂ���B
		m_currentAlpha -= ONE * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha <= ZERO) {
			m_currentAlpha = ZERO;
			m_state = enState_Idle;
		}
		break;
	//�t�F�[�h�A�E�g�X�e�[�g�̎��B
	case enState_FadeOut:
		//�����ɂ��Ȃ��B
		m_currentAlpha += ONE * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha >= ONE) {
			m_currentAlpha = ONE;
			m_state = enState_Idle;
		}
		break;
	//�ҋ@�X�e�[�g�̎��B
	case enState_Idle:
		break;
	}
}
void Fade::Render(RenderContext& rc)
{
	//�摜�̐ݒ�
	if (m_currentAlpha > ZERO) {
		m_spriteRender.SetMulColor({ ONE, ONE, ONE, m_currentAlpha });
		//�摜��`�悷��B
		m_spriteRender.Draw(rc);
	}
}