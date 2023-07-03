#pragma once
namespace nsK2EngineLow {

	class ModelRender :public IRenderer
	{
	public:
		ModelRender();
		~ModelRender();

		void Init(
			const char* filePath,
			bool shadowRecieve,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool isShadowReciever=true,
			int m_maxInstance = 1
		);
		void SetCasterShadow(const bool castershadow)
		{
			m_isShadowCaster = castershadow;
		}

	private:
		RenderTarget albedRT;
		RenderTarget normalRT;
		RenderTarget worldPosRT;
		SpriteInitData spriteInitData;
		Sprite defferdLightinSpr;
	public:

		ModelInitData transModelInitData;
		Model sphereModel;
		Vector3 planePos = { 0.0f,160.0f,20.0f };

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
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}
		void Update();


		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);

		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
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
		void UpdateInstancingData(int instanceNo,const Vector3& pos, const Quaternion& rot, const Vector3& scale);

		/// <summary>
		/// インスタンスを除去。
		/// </summary>
		/// <remark>
		/// インスタンス描画を利用している際に、そのインスタンスをシーンから除去したい場合に利用してください。
		/// </remark>
		/// <param name="instanceNo">インスタンス番号</param>
		void RemoveInstance(int instanceNo);
	private:
		
		void InitSkeleton(const char* filePath);

		void InitShadowModel(
			const char* tkmFilePath,
			EnModelUpAxis modelUpAxis);

	
		void OnRenderShadowMap(
			RenderContext& rc,
			const Matrix& lvpMatrix
		);
		void InitGBuffer(
			const char* tkmFilePath,
			EnModelUpAxis modelUpAxis
		);
		void OnRenderToGBuffer(
			RenderContext& rc
		);

	private:
		Model						m_model;
		Model                       m_shadowmodel;
		Model                       m_gbuffer;
		Model						m_forwardRenderModel;				// フォワードレンダリングの描画パスで描画されるモデル
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
		bool                        m_isShadowCaster = true;
		bool                        m_isSsrCaster = true;
		std::unique_ptr<int[]>		m_instanceNoToWorldMatrixArrayIndexTable;	// インスタンス番号からワールド行列の配列のインデックスに変換するテーブル。
		
	};
}

