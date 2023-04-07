#pragma once
class SoundList :public IGameObject
{
public:
	SoundList();
	~SoundList();
	bool Start();

	const int DASH           = 0; //ダッシュサウンド番号
	const int WALK           = 1; //歩きサウンド番号
	const int DASHFIRST      = 2; //スーパーダッシュ準備完了サウンド番号
	const int DASHMAX        = 3; //スーパーダッシュサウンド番号
	const int JUMPEND        = 4; //着地サウンド番号
	const int DROP           = 5; //ヒップドロップサウンド番号
	const int JUMP           = 6; //ジャンプサウンド番号
	const int DMM            = 7; //スーパーダッシュ移動サウンド番号
	//8
	const int ENEMYDOWN      = 9; //エネミーダウンサウンド番号
	const int ENEMYDOWN2     = 10;//エネミーダウン2サウンド番号
	const int ENEMYDOWNHIP   = 11;//エネミーダウンヒップサウンド番号
	const int BARDMOVE       = 12;//鳥サウンド番号
	const int ENEMYMOVE      = 13;//エネミー移動サウンド番号
	const int ENEMYMOVE2     = 14;//エネミー移動2サウンド番号
	const int FORTIDLE       = 15;//大砲待機サウンド番号
	const int FORTSTAY       = 16;//大砲発射サウンド番号
	const int FORTMOVE       = 17;//大砲移動サウンド番号
	const int GAMEBGM        = 18;//ゲームBGMサウンド番号
	const int ENEMYJUMPCOUNT = 19;//連続踏みつけサウンド番号
	const int TITLEA         = 20;//Aボタン入力サウンド番号
	const int TITLEBGM       = 21;//タイトルBGMサウンド番号
	const int BLOCK          = 22;//ブロック破壊サウンド番号
	const int FALL           = 23;//落下サウンド番号
};