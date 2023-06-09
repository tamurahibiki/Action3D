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
		/// ボーンの名前からボーン番号を検索。
		/// </summary>
		/// <param name="boneName">ボーンの名前</param>
		/// <returns>ボーン番号。見つからなかった場合は-1が返ってきます。</returns>
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		/// <summary>
		/// ボーン番号からボーンを取得。
		/// </summary>
		/// <param name="boneNo">ボーン番号</param>
		/// <returns>ボーン</returns>
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
		/// ワールド行列を取得。
		/// </summary>
		/// <param name="instanceId">
		/// インスタンスID。
		/// この引数はインスタンシング描画が向こうの場合は無視されます。
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
		/// インスタンシングデータの更新。
		/// </summary>
		/// <param name="pos">座標</param>
		/// <param name="rot">回転</param>
		/// <param name="scale">拡大率</param>
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
		
		int							m_numInstance = 0;					// インスタンスの数。
		int							m_maxInstance = 1;					// 最大インスタンス数。
		
		bool						m_isEnableInstancingDraw = false;	// インスタンシング描画が有効？
		std::unique_ptr<Matrix[]>	m_worldMatrixArray;					// ワールド行列の配列。
		StructuredBuffer			m_worldMatrixArraySB;				// ワールド行列の配列のストラクチャードバッファ。
		EnModelUpAxis               m_enFbxUpAxis = enModelUpAxisZ;
	};
}

