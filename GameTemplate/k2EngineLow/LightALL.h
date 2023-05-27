#pragma once

namespace nsK2EngineLow {

    /// <summary>
   /// ���C�g�\���́B
   /// </summary>
    struct Directionlight {
        Vector3 dirDirection;	//���C�g�̕����B
        float pad;
        Vector3 dirColor;
        float pad1;
    public:
        const Vector3& GetDirection()const
        {
            return dirDirection;
        }
    };
    struct Pointlight {
        Vector3 ptPosition;		//�ʒu�B
        float pad;				//�p�f�B���O�B
        Vector3 ptColor;		//�J���[�B
        float ptRange;			//�e���͈́B
    };
    struct Spotlight {
        Vector3 spPosition;		//�ʒu�B
        float pad;				//�p�f�B���O�B
        Vector3 spColor;		//�J���[�B
        float spRange;			//�e���͈́B
        Vector3 spDirection;	//�ˏo�����B
        float spAngle;			//�ˏo�p�x�B
    };

    struct Light {

        Directionlight directionlight; //�f�B���N�V�������C�g�B
        Pointlight pointlight; //�|�C���g���C�g�B
        Spotlight spotlight; //�X�|�b�g���C�g�B

        Vector3 ambientLight;
        float pad;
        Vector3 eyePos;
        float pad2;
    };

    class LightALL
    {
    public:
        LightALL() {}
        ~LightALL();
        void Update();
        void Init();

        /// <summary>
        /// �f�B���N�V�������C�g�̕����B
        /// </summary>
        /// <param name="light">����</param>
        void SetLigDirection(const Vector3& light)
        {
            m_light.directionlight.dirDirection = light;
        }
        /// <summary>
        /// �f�B���N�V�������C�g�̃J���[�B
        /// </summary>
        /// <param name="light">�J���[</param>
        void SetLigColor(const Vector3& color)
        {
            m_light.directionlight.dirColor = color;
        }
        /// <summary>
        /// ������ݒ肷��B
        /// </summary>
        /// <param name="col">�J���[�B</param>
        void SetAmbientLight(const Vector3& col)
        {
            m_light.ambientLight = col;
        }

        /// <summary>
         /// �|�C���g���C�g�̏ꏊ�B
         /// </summary>
         /// <param name="light">�ꏊ</param>
        void SetLigPoint(const Vector3& lightposi)
        {
            m_light.pointlight.ptPosition = lightposi;
        }
        /// <summary>
         /// �|�C���g���C�g�̃J���[�B
         /// </summary>
         /// <param name="light">�J���[</param>
        void SetLigPointColor(const Vector3& lightcola)
        {
            m_light.pointlight.ptColor = lightcola;
        }
        /// <summary>
        /// �͈͂�ݒ�B
        /// </summary>
        /// <param name="range"></param>
        void SetPointRange(float range)
        {
            m_light.pointlight.ptRange = range;
        }

        /// <summary>
         /// �X�|�b�g���C�g�̉�]�B
         /// </summary>
         /// <param name="rot">��]</param>
        void SetLigSpotRot(const Vector3& lightrot)
        {
            m_light.spotlight.spDirection = lightrot;
        }
        /// <summary>
        /// �X�|�b�g���C�g�̏ꏊ�B
        /// </summary>
        /// <param name="posi">�ꏊ</param>
        void SetLigSpot(const Vector3& posi)
        {
            m_light.spotlight.spPosition = posi;
        }
        /// <summary>
        /// �X�|�b�g���C�g�̐F�B
        /// </summary>
        /// <param name="Color">�F</param>
        void SetLigSpotColor(const Vector3& color)
        {
            m_light.spotlight.spColor = color;
        }

        /// <summary>
        /// ���_�̃|�W�V������ݒ肷��B
        /// </summary>
        /// <param name="pos">�J�����̃|�W�V�����B</param>
        void SeteyePosition(const Vector3& pos)
        {
            m_light.eyePos = pos;
        }

        const Vector4& GetDirectionLightDirection()const
        {
            return m_light.directionlight.GetDirection();
        }

        Light& GetLight()
        {
            return m_light;
        }

        const Vector3& GetAmbientLight()
        {
            return m_light.ambientLight;
        }
    private:
        Light               m_light;  //�V�[�����C�g�B

        float posi = 0.0f;
    };
    //�O���[�o���ϐ��B (extern)
    extern LightALL g_Light;
};