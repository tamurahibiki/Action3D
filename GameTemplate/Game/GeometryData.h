#pragma once
#include "geometry/AABB.h"

namespace nsK2Engine {
	class ModelRender;

	class GemometryData{
	public:
		void Init(ModelRender* modelRender, int instanceId);

		bool IsInViewFrustum()const
		{
			return m_isInViewFrustum;
		}
		const Vector3& GetAabbMaxPositionInWorld()const
		{
			return m_aabbMax;
		}
		const Vector3& GetAabbMinPositionInWorld() const
		{
			return m_aabbMin;
		}
		bool IsShadowCaster()const;

		void Update();
	private:
		bool m_isInViewFrustum = false;
		AABB m_aabb;
		Vector3 m_aabbWorldVertexPositions[8];
		Vector3 m_aabbMax;
		Vector3 m_aabbMin;
		ModelRender* m_modelRender = nullptr;
		int m_instanceId = 0;
	};
}

