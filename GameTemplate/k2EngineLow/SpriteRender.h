#pragma once
namespace nsK2EngineLow {
	class SpriteRender:public IRenderer
	{
	public:
		SpriteRender();
		void Init(const char* filePath,
			const float w = 1600.0f,
			const float h = 900.0f,
			AlphaBlendMode AlphaBlendMode = AlphaBlendMode_Trans);

		void Draw(RenderContext& rc);

		/// <summary>
		/// �摜��`�悷�銄���B
		/// </summary>
		/// <param name="x">�`�悷�銄���B1.0f���ő�B</param>
		void SetLimitedX(const float x)
		{
			m_sprite.SetX(x);
		}
		void SetLimitedY(const float y)
		{
			m_sprite.SetY(y);
		}

		/// <summary>
		/// ���_��ݒ�B���_�����Ƃ��Ĉ����̕������摜�𐶐�����B
		/// Left 0.5���ƍ�����܊������摜���`�ʂ����B
		/// </summary>
		/// <param name="isLeft">���_�B</param>
		void SetIsDisplayRestrictionLeftSide(const bool isLeft)
		{
			m_sprite.SetIsDisplayRestrictionLeftSide(isLeft);
		}
		void SetIsDisplayRestrictionRightSide(const bool isRight)
		{
			m_sprite.SetIsDisplayRestrictionRightSide(isRight);
		}

		void SetIsDisplayRestrictionUpSide(const bool isUp)
		{
			m_sprite.SetIsDisplayRestrictionUpSide(isUp);
		}
		void SetIsDisplayRestrictionDownSide(const bool isDown)
		{
			m_sprite.SetIsDisplayRestrictionDownSide(isDown);
		}

		/// <summary>
		/// ���W��ݒ�Bz��0.0f�ŁB
		/// </summary>
		/// <param name="pos">���W�B</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
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
		/// �傫����ݒ�Bz��1.0f�ŁB
		/// </summary>
		/// <param name="scale">�傫���B</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �傫�����擾�B
		/// </summary>
		/// <returns>�傫���B</returns>
		const Vector3& GetScale() const
		{
			return m_scale;
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rot">��]�B</param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
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
		/// �s�{�b�g��ݒ�B
		/// </summary>
		/// <param name="pivot">�s�{�b�g�B</param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// �s�{�b�g���擾�B
		/// </summary>
		/// <returns>�s�{�b�g�B</returns>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}
		/// <summary>
		/// ��Z�J���[��ݒ�B
		/// </summary>
		/// <param name="mulColor">��Z�J���[�B</param>
		void SetMulColor(const Vector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}
		/// <summary>
		/// ��Z�J���[���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector4& GetMulColor() const
		{
			return m_sprite.GetMulColor();
		}
		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update()
		{
			m_sprite.Update(m_position,
				m_rotation,
				m_scale,
				m_pivot);
		}

		void OnRenderSprite2D(RenderContext& rc) override
		{
			if (m_isInit == false)
			{
				return;
			}
			m_sprite.Draw(rc);
		}

	private:
		Sprite			m_sprite;								//�X�v���C�g�B
		Vector3			m_position = Vector3::Zero;				//���W�B
		Quaternion		m_rotation = Quaternion::Identity;		//��]�B
		Vector3			m_scale = Vector3::One;					//�傫���B
		Vector2			m_pivot = Sprite::DEFAULT_PIVOT;		//�s�{�b�g�B
		bool m_isInit = false;
	};
}