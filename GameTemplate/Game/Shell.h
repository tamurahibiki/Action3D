#pragma once
#include"IBgActor.h"
/// <summary>
/// �C�e�N���X
/// </summary>
class Shell :public IBgActor
{
public:
	Shell();
	~Shell();
	bool Start();
	void Update();
	//�����蔻��B
	void Collision();
	//�Փˌ�̏����B
	void CollisionEstablishment();
	void Render(RenderContext& rc);
	
private:
	/// <summary>
	/// �|�����ʉ����Đ�����B
	/// </summary>
	/// <returns>�|�����ʉ����Đ�����Ȃ�true�B</returns>
	bool                    DownSound = true;
	Vector3					m_moveSpeed;						//�ړ����x�B
	float					m_timer = 0.0f;						//�^�C�}�[�B
};