#pragma once
#include "IActor.h"
/// <summary>
/// 敵クラスの基底クラス
/// </summary>
class IEnemy :public IActor
{
public:
    IEnemy() {}  //コンストラクタ
    //エネミーの回転処理
    void EnemyRotation();
    //デストラクタ
    //C++の場合、基底クラスにはvirtualが必要です。
    virtual ~IEnemy() {}
    //派生クラスからアクセスできるように
    //protectedにしておきます。
protected:
	/// <summary>
	/// 倒れる効果音を再生する。
	/// </summary>
	/// <returns>倒れる効果音を再生するならtrue。</returns>
    bool                DownSound = true;
	/// <summary>
	/// 追いかけて移動する。
	/// </summary>
	/// <returns>追いかけて移動するならtrue。</returns>
    bool                Move = false;
 
    CharacterController m_charaCon;                 //キャラクターコントローラー
    Vector3             m_moveSpeed;                //移動速度
    Vector3             m_inertiaSpeed;             //慣性
};