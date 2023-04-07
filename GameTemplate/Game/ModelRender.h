#pragma once
//#include "IRenderer.h"

namespace nsK2EngineLow {

	class ModelRender:public IRenderer
	{
	public:
		ModelRender();
		~ModelRender();

		void Init(
			const char* filePath,
			AnimationClip* animationClips = nullptr,
			int m_numAnimationClips=0,
			EnModelUpAxis EnModelUpAxis=enModelUpAxisZ,
			int m_maxInstance=1
			);
	public:
		void InitModel(const char* filePath);

		void modelUpdate();

		ModelInitData m_modelInitData;
		Model spheremodel;
		Vector3 planPos = { 0.0f,160.0f,20.0f };
		
		void Draw(RenderContext& rc);

		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}

		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}
		void Update();

		

		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);

		void PlayAnimation(int animNo, float interpolateTime=0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		bool IsPlayingAnimation()const
		{
			return m_animation.IsPlaying();
		}

		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}
		/// <summary>
		/// �{�[���̖��O����{�[���ԍ��������B
		/// </summary>
		/// <param name="boneName">�{�[���̖��O</param>
		/// <returns>�{�[���ԍ��B������Ȃ������ꍇ��-1���Ԃ��Ă��܂��B</returns>
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		/// <summary>
		/// �{�[���ԍ�����{�[�����擾�B
		/// </summary>
		/// <param name="boneNo">�{�[���ԍ�</param>
		/// <returns>�{�[��</returns>
		Bone* GetBone(int boneNo) const
		{
			return m_skeleton.GetBone(boneNo);
		}

		Model& GetModel()
		{
			return m_model;
		}

		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}

		bool IsInstancingDraw() const
		{
			return m_isEnableInstancingDraw;
		}
		/// <summary>
		/// ���[���h�s����擾�B
		/// </summary>
		/// <param name="instanceId">
		/// �C���X�^���XID�B
		/// ���̈����̓C���X�^���V���O�`�悪�������̏ꍇ�͖�������܂��B
		/// </param>
		/// <returns></returns>
		const Matrix& GetWorldMatrix(int instanceId) const
		{
			if (IsInstancingDraw()) {
				return m_worldMatrixArray[instanceId];
			}
			return m_model.GetWorldMatrix();
		}
		/// <summary>
		/// �C���X�^���V���O�f�[�^�̍X�V�B
		/// </summary>
		/// <param name="pos">���W</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g�嗦</param>
		void UpdateInstancingData(const Vector3& pos, const Quaternion& rot, const Vector3& scale);
		
		private:
			void InitSkeletonz(const char* filePath);
		
	private:
		Model						m_model;

		Skeleton                    m_skeleton;
		float                       m_animationSpeed = 1.0f;
		AnimationClip*              m_animationClips = nullptr;
		int                         m_numAnimationClips = 0;
		Animation                   m_animation;
		Vector3                     m_position;
		Quaternion	 				m_rotation;
		Vector3						m_scale;
		Model                       m_zprepassModel;
		
		int							m_numInstance = 0;					// �C���X�^���X�̐��B
		int							m_maxInstance = 1;					// �ő�C���X�^���X���B
		
		bool						m_isEnableInstancingDraw = false;	// �C���X�^���V���O�`�悪�L���H
		std::unique_ptr<Matrix[]>	m_worldMatrixArray;					// ���[���h�s��̔z��B
		StructuredBuffer			m_worldMatrixArraySB;				// ���[���h�s��̔z��̃X�g���N�`���[�h�o�b�t�@�B
		EnModelUpAxis               m_enFbxUpAxis = enModelUpAxisZ;
	};
}

