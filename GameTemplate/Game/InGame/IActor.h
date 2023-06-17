#pragma once
#include <CollisionObject.h>
#include "InGame/Player/Player.h"
#include "EffectList.h"
#include "SoundList.h"

/// <summary>
/// ���N���X
/// </summary>
namespace App {
	class IActor :public IGameObject
	{
	public:
		IActor() {}  //�R���X�g���N�^
		//�f�X�g���N�^
		//C++�̏ꍇ�A���N���X�ɂ�virtual���K�v�ł��B
		virtual ~IActor() {}
		//���W�E��]�E�傫����ݒ肵�A���f�����X�V����B
		void SetupTRS();
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="position">���W�B</param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// ���W���擾�B
		/// </summary>
		/// <returns>���W�B</returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rotation">��]�B</param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}
		/// <summary>
		/// ��]���擾�B
		/// </summary>
		/// <returns>��]�B</returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}
		/// <summary>
		/// �傫����ݒ�B
		/// </summary>
		/// <param name="scale">�傫���B</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		//�h���N���X����A�N�Z�X�ł���悤��
		//protected�ɂ��Ă����܂��B
	protected:
		ModelRender           m_modelRender;              //���f�������_�[
		Vector3               m_position;                 //���W
		Quaternion            m_rotation;                 //��]
		Vector3               m_scale;                    //�傫��
		Vector3			      m_forward = Vector3::AxisZ; //���ʃx�N�g��
		Player* m_player = nullptr;         //�v���C���[
		CollisionObject* m_collisionObject = nullptr;//�R���W�����I�u�W�F�N�g
		EffectEmitter* m_effectEmitter = nullptr;  //�G�t�F�N�g
		EffectList* m_effectlist = nullptr;     //�G�t�F�N�g���X�g
		SoundList* m_soundlist = nullptr;      //�T�E���h���X�g
	};
}