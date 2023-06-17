#pragma once
#include <CollisionObject.h>
#include "InGame/Player/Player.h"
#include "EffectList.h"
#include "SoundList.h"

/// <summary>
/// 基底クラス
/// </summary>
namespace App {
	class IActor :public IGameObject
	{
	public:
		IActor() {}  //コンストラクタ
		//デストラクタ
		//C++の場合、基底クラスにはvirtualが必要です。
		virtual ~IActor() {}
		//座標・回転・大きさを設定し、モデルを更新する。
		void SetupTRS();
		/// <summary>
		/// 座標を設定。
		/// </summary>
		/// <param name="position">座標。</param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// 座標を取得。
		/// </summary>
		/// <returns>座標。</returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <param name="rotation">回転。</param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}
		/// <summary>
		/// 回転を取得。
		/// </summary>
		/// <returns>回転。</returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}
		/// <summary>
		/// 大きさを設定。
		/// </summary>
		/// <param name="scale">大きさ。</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		//派生クラスからアクセスできるように
		//protectedにしておきます。
	protected:
		ModelRender           m_modelRender;              //モデルレンダー
		Vector3               m_position;                 //座標
		Quaternion            m_rotation;                 //回転
		Vector3               m_scale;                    //大きさ
		Vector3			      m_forward = Vector3::AxisZ; //正面ベクトル
		Player* m_player = nullptr;         //プレイヤー
		CollisionObject* m_collisionObject = nullptr;//コリジョンオブジェクト
		EffectEmitter* m_effectEmitter = nullptr;  //エフェクト
		EffectList* m_effectlist = nullptr;     //エフェクトリスト
		SoundList* m_soundlist = nullptr;      //サウンドリスト
	};
}