#pragma once
class EffectList:public IGameObject
{
public:
	EffectList();
	~EffectList();
	bool Start();
	
	const int MOVE        = 0; //ダッシュ移動エフェクト番号
	const int WALK        = 1; //歩き移動エフェクト番号
	const int DASHFIRST   = 2; //スーパーダッシュ準備完了エフェクト番号
	const int DASHMAX     = 3; //スーパーダッシュエフェクト番号
	const int BLOCK       = 4; //ブロック破壊エフェクト番号
	const int DMF         = 5; //火花エフェクト番号
	const int JUMP        = 6; //ジャンプエフェクト番号
	const int DROP        = 7; //ヒップドロップ着地エフェクト番号
	const int DMF2        = 8; //焦げ跡エフェクト番号
	const int ENEMYMOVE   = 9; //エネミー移動エフェクト番号
	const int FORTMOVE    = 10;//大砲移動エフェクト番号
	const int CLEAR       = 11;//クリアエフェクト番号
	const int ENEMYDAMAGE = 12;//エネミーダメージエフェクト番号
};

