#pragma once
#include "InGame/IActor.h"
/// <summary>
/// 背景モデルの基底クラス
/// </summary>
namespace App {
	class IBgActor :public IActor
	{
	public:
		IBgActor() {}  //コンストラクタ
		//デストラクタ
		//C++の場合、基底クラスにはvirtualが必要です。
		virtual ~IBgActor() {}
		//派生クラスからアクセスできるように
		//protectedにしておきます。
	protected:
		PhysicsStaticObject   m_physicsStaticObject;      //静的物理オブジェクト
	};
}