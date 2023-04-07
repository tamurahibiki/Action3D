#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Game.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "CollisionObject.h"
#include "Fort.h"
#include "FortTop.h"
#include "GoalPoint.h"
#include "EffectList.h"
#include "SoundList.h"

namespace
{
	const float ZERO = 0.0f;//ゼロ
	//////////////////////////////////////
	////ここからプレイヤーの初期設定の定数を定義する。
	//////////////////////////////////////
	const Vector3 MODELSCALE = { 0.5f, 0.5f, 0.5f };          //モデルの大きさ
	const Vector3 TRYPOS     = { -2000.0f, 100.0f, 33000.0f };//中間地点到達後、リスポーン座標
	const float FIRSTADDITIONROTY = 80.0f; //初期位置で加算する回転
	const float FALLDEAD          = 200.0f;//落下死亡ライン
	//////////////////////////////////////
	////プレイヤーの初期設定の定数を定義するのはここまで。
	//////////////////////////////////////
	
	//////////////////////////////////////
	////ここからプレイヤーの移動の定数を定義する。
	//////////////////////////////////////
	const float GRAVITY                   = 30.0f;  //通常時の重力
	const float JUMPUPGRAVITY             = 18.0f;  //ジャンプ上昇時の重力
	const float DROPGRAVITY               = 700.0f; //ヒップドロップ時の重力
	const float FALLHEDGRAVITY            = 15.0f;  //死亡時。ブロック衝突時の重力
	const float SJUMP                     = 10.0f;  //長押しで加算するジャンプ力
	const float FJUMP                     = 400.0f; //最初のジャンプ力
	const float NJUMP                     = 200.0f; //踏みつけ後、追加入力しなかったジャンプ力
	const float MAXJUMPSPEED              = 1000.0f;//通常ジャンプ時の最高速度
	const float MAXJUMPCOUNTSPEED         = 350.0f; //踏み台ジャンプ時の最高速度
	const float WALK                      = 200.0f; //歩く速度
	const float DASH                      = 300.0f; //ダッシュ速度
	const float MAXDASH                   = 350.0f; //スーパーダッシュ速度
	const float INERTIAMULTIPLICATION     = 0.95f;  //慣性移動時、乗算する速度
	const float FORTINERTIAMULTIPLICATION = 0.2f;   //大砲慣性移動時、乗算する速度
	const float FORTGROUNDMULTIPLICATION  = 0.4f;   //大砲移動(地上)時、乗算される速度
	const float GOALMULTIPLICATION        = 20.0f;  //ゴール時、乗算される速度
	const float ONGROUNDMOVE              = 150.0f; //回転する地面に乗っている時に加算される速度
	const float FORTIDLE                  = 55.0f;  //大砲発射前速度
	const float FORTMOVE                  = 670.0f; //大砲発射後速度
	//////////////////////////////////////
	////プレイヤーの移動の定数を定義するのはここまで。
	//////////////////////////////////////
	
	//////////////////////////////////////
	////ここからプレイヤーの当たり判定の定数を定義する。
	//////////////////////////////////////
	const float CHARACONRADIUSGROUND = 90.0f; //地上時のキャラクターコントローラーの半径
	const float CHARACONHEIGHTGROUND = 80.0f; //地上時のキャラクターコントローラーの高さ
	const float CHARACONHITBLOCK     = 60.0f; //ブロック衝突時のキャラクターコントローラーの半径、高さ
	const float BODYCOLLISIONSCALE   = 140.0f;//Bodyコリジョンの大きさ
	const float HEDCOLLISIONPOSY     = 500.0f;//頭のコリジョンの高さ
	const float LEGCOLLISIONPOSY     = 100.0f;//足のコリジョンの高さ
	const float HIPCOLLISIONPOSY     = 150.0f;//お尻のコリジョンの高さ
	const Vector3 HEDCOLLISIONSCALE  = { 120.0f, 200.0f, 120.0f };//頭のコリジョンの大きさ
	const Vector3 LEGCOLLISIONSCALE  = { 50.0f, 50.0f, 50.0f };   //足のコリジョンの大きさ
	const Vector3 HIPCOLLISIONSCALE  = { 150.0f, 150.0f, 150.0f };//お尻のコリジョンの大きさ
	//////////////////////////////////////
	////プレイヤーの当たり判定の定数を定義するのはここまで。
	//////////////////////////////////////

	//////////////////////////////////////
	////ここからゲームパッドの左スティックの定数を定義する。
	//////////////////////////////////////
	const float BLOCKHEDSTICK     = 0.1f;//ブロックが頭に衝突した時に乗算する左スティック入力量
	const float AIRSTICK          = 0.7f;//空中にいる時に乗算する左スティック入力量
	const float LASTFRAMESTICKDOT = 0.9f;//左スティックの入力量の内積
	//////////////////////////////////////
	////ゲームパッドの左スティックの定数を定義するのはここまで。
	//////////////////////////////////////

	//////////////////////////////////////
	////ここからゲームカメラの定数を定義する。
	//////////////////////////////////////
	const float   CAMERAFAR = 320000.0f;                 //遠平面までの距離
	const Vector3 CAMERAPOS = { 0.0f, 1000.0f,-1000.0f };//カメラの座標
	//////////////////////////////////////
	////ゲームカメラの定数を定義するのはここまで。
	//////////////////////////////////////
	
	//////////////////////////////////////
	////ここからタイマーの定数を定義する。
	//////////////////////////////////////
	const float SPAWNTIME         = 1.0f;//スポーン直後の初期化する時間
	const float UITIMEMAX         = 2.0f;//UIの表示を開始する時間
	const float STARTTIMEMAX      = 1.9f;//プレイヤーの操作が開始できる時間
	const float IDLETIMEMAX       = 6.0f;//放置中待機ステートにする時間
	const float DASHTIMEMAX       = 2.0f;//スーパーダッシュになる時間
	const float DROPTIMEMAX       = 0.5f;//ヒップドロップの着地硬直が終了する時間
	const float JUMPTIMEMAX       = 0.2f;//ジャンプのクールタイムが終了する時間
	const float JUMPINPUTTIMEMAX  = 0.6f;//ジャンプボタン入力受付時間
	const float FORTTIMEMAX       = 0.4f;//大砲移動(地上)時間
	const float MOVEEFFECTTIMEMAX = 0.3f;//エフェクトを再生開始時間
	//////////////////////////////////////
	////タイマーの定数を定義するのはここまで。
	//////////////////////////////////////
	
	//////////////////////////////////////
	////ここからエフェクトの定数を定義する。
	//////////////////////////////////////
	const Vector3 WALKDASHEFFECTSCALE = { 50.0f,50.0f,50.0f };   //歩き、ダッシュのエフェクトの大きさ
	const Vector3 DMFEFFECTSCALE      = { 60.0f,50.0f,50.0f };   //火花のエフェクトの大きさ
	const Vector3 DMF2EFFECTSCALE     = { 30.0f,30.0f,30.0f };   //焦げ跡のエフェクトの大きさ
	const Vector3 JUMPEFFECTSCALE     = { 40.0f,20.0f,40.0f };   //ジャンプのエフェクトの大きさ
	const Vector3 DROPEFFECTSCALE     = { 50.0f,60.0f,50.0f };   //ヒップドロップのエフェクトの大きさ
	const Vector3 CLEAREFFECTSCALE    = { 100.0f,100.0f,100.0f };//クリアのエフェクトの大きさ
	//////////////////////////////////////
	////エフェクトの定数を定義のはここまで。
	//////////////////////////////////////
	
	//////////////////////////////////////
	////ここから画像の定数を定義する。
	//////////////////////////////////////
	const Vector2 ATCSPRITEPIVOT = { 0.0f, 0.5f };           //アイコン、制限時間、クリア画像のピボット
	const Vector3 AICONSPRITEPOS = { -800.0f, 370.0f, 0.0f };//アイコン画像の座標
	const Vector3 TIMERSPRITEPOS = { 550.0f, 385.0f, 0.0f }; //制限時間画像の座標
	const Vector3 CLEARSPRITEPOS = { -400.0f, 100.0f, 0.0f };//クリア画像の座標
	//////////////////////////////////////
	////画像の定数を定義するのはここまで。
	//////////////////////////////////////

	//////////////////////////////////////
	////ここからフォント関係の定数を定義する。
	//////////////////////////////////////
	/// <summary>
	/// HP(残機)
	/// </summary>
	const Vector2 HPFONTPIVOT       = { 1.0f,1.0f };          //HPフォントのピボット
	const Vector3 HPFONTPOS         = { -785.0f,460.0f,0.0f };//HPフォントの座標
	const float   HPFONTSCALE       = 1.3f;                   //HPフォントの大きさ
	const float   HPFONTOFFSET      = 3.0f;                   //HPフォントのオフセット量
	const int     HPFONTCOLORRED    = 1;                      //赤色にする残りHP
	const int     HPFONTCOLORYELLOW = 3;                      //黄色にする残りHP
	/// <summary>
	/// 制限時間
	/// </summary>
	const Vector2 TIMEFONTPIVOT       = { 0.0f,0.0f };         //制限時間フォントのピボット
	const Vector3 TIMEFONTPOS         = { 760.0f,550.0f,0.0f };//制限時間フォントの座標
	const float   TIMEFONTSCALE       = 2.0f;                  //制限時間フォントの大きさ
	const float   TIMEFONTOFFSET      = 3.0f;                  //制限時間フォントのオフセット量
	const int     TIMEFONTCOLORRED    = 30;                    //赤色にする残り制限時間
	const int     TIMEFONTCOLORYELLOW = 100;                   //黄色にする残り制限時間
	//////////////////////////////////////
	////フォント関係の定数を定義するのはここまで。
	//////////////////////////////////////
}

Player::Player(){}
Player::~Player() 
{
	//ゲームカメラを削除する。
	DeleteGO(m_gameCamera);
}
bool Player::Start()
{
	//画像を読み込む。
	InitSprite();
	m_game = FindGO<Game>("game");
	//アニメーションを読み込む。
	InitAnimation();
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/player/Player.tkm", false, m_animClips, enAnimationCilp_Num);
	//中間地点に到達しているなら
	if (m_game->Try == true)
	{
		//スポーン地点を変える
		m_position = TRYPOS;
		//回転を設定する。
		m_modelRender.SetRotation(m_rotation);
	}
	else
	{
		//座標を設定する。
		m_modelRender.SetPosition(m_position);
		//回転を設定する。
		m_modelRender.SetRotation(m_rotation);
		m_rotation.SetRotationY(FIRSTADDITIONROTY);
	}
	//大きさを設定する。
	m_modelRender.SetScale(MODELSCALE);
	//モデルを更新する。
	m_modelRender.Update();
	//当たり判定を作成する。
	m_charaCon.Init(
		CHARACONRADIUSGROUND,//半径
		CHARACONHEIGHTGROUND,//高さ
		m_position//座標
	);
	//アニメーションイベント用の関数を設定する。
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});
	//プレイヤーが生まれた直後なら
	if (m_game->PlayerSpawn == true)
	{
		//開始時間を1.0秒からスタートする。
		m_startTime = SPAWNTIME;
		m_UITime = SPAWNTIME;
		m_game->PlayerSpawn = false;
	}

	//ゲームカメラの座標を設定する。
	g_camera3D->SetPosition(CAMERAPOS);
	//遠平面を設定する。
	g_camera3D->SetFar(CAMERAFAR);
	//ゲームカメラオブジェクトを作成する。
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	
	m_effectlist = FindGO<EffectList>("effectlist");
	m_soundlist = FindGO<SoundList>("soundlist");
	
	m_fort    = FindGO<Fort>("fort");
	m_fortTop = FindGO<FortTop>("forttop");
	m_goal    = FindGO<GoalPoint>("goalpoint");
	return true;
}
void Player::Update()
{
	//制限時間が0秒になったら
	if (m_game->m_gameTime <= ZERO)
	{
		//プレイヤー死亡後の処理に遷移する。
		m_game->Retry();
		return;
	}
	//UI表示開始タイマーが2.0秒以下なら
	if (m_UITime < UITIMEMAX)
	{
		//UI表示開始タイマーを加算する。
		m_UITime += g_gameTime->GetFrameDeltaTime();
	}
	//操作開始タイマーが1.9秒以下なら
	if (m_startTime < STARTTIMEMAX)
	{
		//操作開始タイマーを加算する。
		m_startTime += g_gameTime->GetFrameDeltaTime();
		return;
	}
	//HPの処理。
	HP();
	//制限時間の処理。
	TimeLimit();
	//左スティックが操作されていたら
	if (g_pad[0]->GetLStickXF() && g_pad[0]->GetLStickYF())
	{
		//左スティックが操作されている。
		Stick = true;
	}
	//左スティックが操作されていないなら
	else if (!g_pad[0]->GetLStickXF() && !g_pad[0]->GetLStickYF())
	{
		//左スティックが操作されていない。
		Stick = false;
	}
	//落下死亡ラインを超えていたら
	if (m_position.y < -FALLDEAD)
	{
		//落下の効果音を1度だけする。
		if (Fall_SE == true)
		{
			//効果音を設定する。
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(23);
			se->Play(false);//ループ再生しない。
			se->SetVolume(0.2f);//ボリュームの設定。
			Fall_SE = false;
		}
		//死亡状態にする。
		Dead = true;
		//落下状態にする。
		Fall = true;
		//落下ステートに遷移する。
		m_playerState = enPlayerState_Fall;
	}
	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//コリジョンの座標を設定する。
	Vector3 m_bodyposition = m_position;
	m_bodyposition.y = m_position.y + 200.0f;
	//球形状のコリジョンを作成する。
	m_collisionObject->CreateSphere(
		m_bodyposition, //座標
		Quaternion::Identity, //回転
		BODYCOLLISIONSCALE//大きさ
	);
	////名前をBodyにする。
	m_collisionObject->SetName("Body");
	
	//移動処理。
	Move();
	//回転処理。
	Rotation();
	//当たり判定。
	Collision();
	//ステートの遷移処理。
	ManageState();
	//アニメーションの再生。
	PlayAnimation();
	//モデルの更新。
	m_modelRender.Update();
}
void Player::Move()
{
	//落下ステートかブロックに頭が衝突していたら
	if (m_playerState == enPlayerState_Fall || Block_Hed == true)
	{
		//落下ステートなら
		if (m_playerState == enPlayerState_Fall)
		{
			//x.z方向の移動速度を0にする。
			m_moveSpeed.x = ZERO;
			m_moveSpeed.z = ZERO;
		}
		//重力を半分にする。
		m_moveSpeed.y -= FALLHEDGRAVITY;
	}
	//死亡ステートなら
	if (m_playerState==enPlayerState_Dead)
	{
		//ここから先は処理しない。
		return;
	}
	//ゴール時の処理。
	Move_Goal();
	//大砲時の処理。
	Move_Fort();
	//大砲移動、ゴール、死亡、いずれもしていないなら
	if (Fort_Idle == false && Fort_Move == false
		&& Fort_Top == false && Goal == false && Goal2 == false && Fall == false)
	{ 
		//スティックの入力量処理。
		Move_Stick();
		//地上移動処理。
		Move_Ground();
		//空中移動処理。
		Move_Air();
	}
	//連続で踏みつけ数が2なら
	if (Enemy_JunpCount == 2)
	{
		//効果音を再生する。
		if (Enemy_JumpCountSE == true)
		{
			/*m_bgm = NewGO<SoundSource>(0);
			m_bgm->Init(19);
			m_bgm->Play(false);
			m_bgm->SetVolume(0.5f);
			Enemy_JumpCountSE = false;*/
		}
	}
	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_charaCon.Execute(m_moveSpeed, 5.0f / 60.0f);
	m_lastFrameMoveDirection = m_moveSpeed;
	m_lastFrameMoveDirection.Normalize();
	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);	
}
void Player::Move_Stick()
{
	//x.z方向の移動速度を0にする。
	m_moveSpeed.x = ZERO;
	m_moveSpeed.z = ZERO;
	Vector3 stickL;
	//地上にいるなら
	if (m_charaCon.IsOnGround())
	{
		//左スティックの入力量をそのまま渡す。
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();
	}
	//ヒップドロップ中なら
	else if (Stop == true || Drop == true)
	{
		//左スティックの入力量を0にする。
		stickL.x = g_pad[0]->GetLStickXF() * ZERO;
		stickL.y = g_pad[0]->GetLStickYF() * ZERO;
	}
	//ブロックが頭に衝突しているなら
	else if (Block_Hed == true)
	{
		//左スティックの入力量を0.1倍にする。
		stickL.x = g_pad[0]->GetLStickXF() * BLOCKHEDSTICK;
		stickL.y = g_pad[0]->GetLStickYF() * BLOCKHEDSTICK;
	}
	//空中で
	else
	{
		//ブロックに衝突していないなら
		if (HitBlock == false)
		{
			//左スティックの入力量を0.7倍にする。
			stickL.x = g_pad[0]->GetLStickXF() * AIRSTICK;
			stickL.y = g_pad[0]->GetLStickYF() * AIRSTICK;
		}
		//ブロックに衝突しているなら
		else
		{
			//左スティックの入力量を0にする。
			stickL.x = g_pad[0]->GetLStickXF() * ZERO;
			stickL.y = g_pad[0]->GetLStickYF() * ZERO;
		}
	}
	//カメラの前方向のベクトルを持ってくる。
	Vector3 forward;
	//カメラの右方向のベクトルを持ってくる。
	Vector3 right;
	//カメラの前方向を持ってくる。
	forward = g_camera3D->GetForward();
	//カメラの右方向を持ってくる。
	right = g_camera3D->GetRight();
	//y方向のベクトルを0にする。
	forward.y = ZERO;
	right.y = ZERO;
	//XかYボタンを押していて、ダッシュした時間が2秒以下なら
	if (g_pad[0]->IsPress(enButtonX) && m_dashTime < DASHTIMEMAX
		|| g_pad[0]->IsPress(enButtonY) && m_dashTime < DASHTIMEMAX)
	{
		//ダッシュした時間を加算する。
		m_dashTime += g_gameTime->GetFrameDeltaTime();
		//左スティックの入力量にダッシュ速度を乗算する。
		right *= stickL.x * DASH;
		forward *= stickL.y * DASH;
	}
	//XかYボタンを押していて、ダッシュした時間が2秒以上なら
	else if (g_pad[0]->IsPress(enButtonX) && m_dashTime > DASHTIMEMAX
		|| g_pad[0]->IsPress(enButtonY) && m_dashTime > DASHTIMEMAX)
	{
		//左スティックの入力量にスーパーダッシュ速度を乗算する。
		right *= stickL.x * MAXDASH;
		forward *= stickL.y * MAXDASH;
	}
	//XかYボタンを押していないなら
	else
	{
		//ダッシュした時間を0にする。
		m_dashTime = ZERO;
		//左スティックの入力量に歩く速度を乗算する。
		right *= stickL.x * WALK;
		forward *= stickL.y * WALK;
	}
	//左スティックが操作されているなら
	if (Stick == true)
	{
		//1フレーム前の移動方向を使うなら
		if (m_usingLastFrameMoveDirection) {
			//左スティックの入力量の内積が0.9以下になったら
			if (m_lastFrameLStick.Dot(stickL) < LASTFRAMESTICKDOT) {
				//1フレーム前の移動方向を使わない。
				m_usingLastFrameMoveDirection = false;
			}
			//1フレーム前の移動方向を使い処理する。
			m_moveSpeed += m_lastFrameMoveDirection * (right + forward).Length();
		}
		//1フレーム前の移動方向を使わないなら
		else {
			//1フレーム前の移動方向に現在の左スティックの入力量を渡しておく。
			m_lastFrameLStick.x = stickL.x;
			m_lastFrameLStick.y = stickL.y;
			//移動速度を計算する。
			m_moveSpeed += right + forward;
		}
		//慣性速度に現在の移動速度を渡しておく。
		m_inertiaSpeed = m_moveSpeed;
	}
	//左スティックが操作されていないなら
	else if (Stick == false)
	{
		//1フレーム前の移動方向を使わない。
		m_usingLastFrameMoveDirection = false;
		//ダッシュした時間を0にする。
		m_dashTime = ZERO;
		//ブロックの上にいないなら
		if (OnBlock == false)
		{
			//慣性速度に0.95fを乗算する。
			m_inertiaSpeed *= INERTIAMULTIPLICATION;
		}
		//y方向の移動速度を0にする。
		m_inertiaSpeed.y = ZERO;
		//現在の移動速度に慣性速度を渡しておく。
		m_moveSpeed += m_inertiaSpeed;
	}
}
void Player::Move_Ground()
{
	//地面に付いているか、ブロックの上にいたら。
	if (m_charaCon.IsOnGround() || OnBlock == true)
	{
		//当たり判定を削除する。
		m_charaCon.RemoveRigidBoby();
		//当たり判定を作成する。
		m_charaCon.Init(
			CHARACONRADIUSGROUND,//半径
			CHARACONHEIGHTGROUND,//高さ
			m_position//座標
		);
		//ブロックが頭に衝突していない。
		Block_Hed = false;
		//ブロックが体に衝突していない。
		HitBlock = false;
		//連続踏みつけ数を0にする。
		Enemy_JunpCount = ZERO;
		//連続踏みつけの効果音を再生できるようにする。
		Enemy_JumpCountSE = true;
		//ジャンプ中の処理をしない。
		PlayerJunp = false;
		//重力を無くす。
		m_moveSpeed.y = ZERO;
		//ジャンプボタンの入力時間を0にする。
		m_jumpInputTime = ZERO;
		//ジャンプが可能な状態にする。
		SecondJump = true;
		//プレイヤーが回転する地面に乗っていたら
		if (OnGroundMove==true)
		{
			//-Z方向の移動速度を増やす、またはz方向の移動速度を減らす。
			m_moveSpeed.z -= ONGROUNDMOVE;
		}
		//ヒップドロップの着地硬直時間が終わっていなかったら
		if (m_dropTime <= DROPTIMEMAX)
		{
			//ヒップドロップの着地硬直時間を経過させていく。
			m_dropTime += g_gameTime->GetFrameDeltaTime();
			//x.z方向の移動速度を0にする。
			m_moveSpeed.x = ZERO;
			m_moveSpeed.z = ZERO;
			//着地エフェクトを再生できるなら
			if (Jump_End_Effect == true)
			{
				//ヒップドロップの着地エフェクトを再生する。
				Drop_EndEffect();
				Jump_End_Effect = false;
				//効果音を設定する。
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(m_soundlist->DROP);
				//ループ再生しない。
				se->Play(false);
				//ボリュームの設定。
				se->SetVolume(0.3f);
			}
			return;
		}
		//ジャンプのクールタイムを経過させていく。
		m_jumpTime += g_gameTime->GetFrameDeltaTime();
		//ジャンプのクールタイムが終わっているなら
		if (m_jumpTime >= JUMPTIMEMAX)
		{
			//AかBボタンを押しているなら
			if (g_pad[0]->IsPress(enButtonA) || g_pad[0]->IsPress(enButtonB))
			{
				//ジャンプステートに遷移する。
				m_playerState = enPlayerState_Jump;
				//ジャンプさせる。
				m_moveSpeed.y += FJUMP;
				//効果音を設定する。
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(m_soundlist->JUMP);
				//ループ再生しない。
				se->Play(false);
				//ボリュームの設定。
				se->SetVolume(0.2f);
				//ジャンプ中にする。
				PlayerJunp = true;
			}
		}
	}
}
void Player::Move_Air()
{
	//空中にいるなら
	if (!m_charaCon.IsOnGround() && OnBlock == false)
	{
		//着地エフェクトを再生できるようにする。。
		Jump_End_Effect = true;
		//移動エフェクトの再生開始時間を0にする。
		m_moveTime = ZERO;
		//ジャンプのクールタイムを初期化する。
		m_jumpTime = ZERO;
		//ヒップドロップ(降下中)なら
		if (Drop == true)
		{
			//お尻の攻撃判定を作成する。
			HipCollision();
		}
		//ヒップドロップ(降下中)でないなら
		if (Drop == false)
		{
			//ヒップドロップ(降下前)なら
			if (Stop == true)
			{
				//重力をなくす。
				m_moveSpeed.y = ZERO;
			}
			////ヒップドロップ(降下前)でないなら
			else if (Stop == false)
			{
				//足の攻撃判定を作成する。
				LegCollision();
				//通常の重力なら
				if (Gravity == true)
				{
					//重力を発生させる。
					m_moveSpeed.y -= GRAVITY;
				}
				//ジャンプ上昇中の重力なら
				else if (Gravity == false)
				{
					//重力を発生させる。
					m_moveSpeed.y -= JUMPUPGRAVITY;
					//頭の攻撃判定を作成する。
					HedCollision();
				}
			}
		}
		//ジャンプが可能な状態なら
		if (SecondJump == true)
		{
			//AかBボタンを押していて、入力時間が0.6秒以下なら
			if (g_pad[0]->IsPress(enButtonA) && m_jumpInputTime < JUMPINPUTTIMEMAX
				|| g_pad[0]->IsPress(enButtonB) && m_jumpInputTime < JUMPINPUTTIMEMAX)
			{
				//ジャンプボタンの入力時間を加算する。
				m_jumpInputTime += g_gameTime->GetFrameDeltaTime();

				//Y方向の移動速度が1000.0f以下なら
				if (m_moveSpeed.y <= MAXJUMPSPEED)
				{
					//ジャンプ力を加算する。
					m_moveSpeed.y += SJUMP;
				}
				//Y方向の移動速度が1000.0f以上なら
				else
				{
					//Y方向の移動速度を1000.0fにする。
					m_moveSpeed.y = MAXJUMPSPEED;
				}
			}
			//ジャンプボタンの入力時間が0.6秒以上なら
			else
			{
				//ジャンプが不可能な状態にする。
				SecondJump = false;
			}
		}
		//LB2かRB2ボタンを押しているなら
		if (g_pad[0]->IsTrigger(enButtonLB2) || g_pad[0]->IsTrigger(enButtonRB2))
		{
			//ヒップドロップステートに遷移する。
			m_playerState = enPlayerState_Drop;
			//ヒップドロップの着地硬直時間を初期化する。
			m_dropTime = ZERO;
			//ヒップドロップの着地硬直時間を加算する。
			m_dropTime += g_gameTime->GetFrameDeltaTime();
		}
		//踏み台ジャンプが可能なら
		if (JunpCount == true)
		{
			//Y方向の移動速度を0にする。
			m_moveSpeed.y = ZERO;
			//踏み台ジャンプを不可能にする。
			JunpCount = false;
			//AかBボタンを押しているなら
			if (g_pad[0]->IsPress(enButtonA) || g_pad[0]->IsPress(enButtonB))
			{
				//Y方向の移動速度が350.0f以下なら
				if (m_moveSpeed.y <= MAXJUMPCOUNTSPEED)
				{
					//ジャンプ力を加算する。
					m_moveSpeed.y += FJUMP;
				}
				//Y方向の移動速度が350.0f以上なら
				else
				{
					//Y方向の移動速度を350.0fにする。
					m_moveSpeed.y = MAXJUMPCOUNTSPEED;
				}
			}
			//AかBボタンを押していないなら
			else
			{
				//Y方向の移動速度が350.0f以下なら
				if (m_moveSpeed.y <= MAXJUMPCOUNTSPEED)
				{
					//低いジャンプ力を加算する。
					m_moveSpeed.y += NJUMP;
				}
				//Y方向の移動速度が350.0f以上なら
				else
				{
					//Y方向の移動速度を350.0fにする。
					m_moveSpeed.y = MAXJUMPCOUNTSPEED;
				}
			}
			//ジャンプステートに遷移する。
			m_playerState = enPlayerState_Jump;
		}
	}
}
void Player::Move_Fort()
{
	//大砲に乗り込むなら
	if (Fort_Idle == true)
	{
		//大砲からプレイヤーに向かうベクトルを計算する。
		Vector3 diff = m_fort->GetPosition() - m_position;
		//プレイヤーから大砲に向かうベクトルを正規化する。
		diff.Normalize();
		//移動速度を計算する
		m_moveSpeed = diff * FORTIDLE;
		//大砲移動(空中)ステートに遷移する。
		m_playerState = enPlayerState_Fort_Air;
	}
	//大砲移動で上昇しているなら
	if (Fort_Move == true)
	{
		//大砲移動(空中)ステートに遷移する。
		m_playerState = enPlayerState_Fort_Air;
		//大砲移動の頂点ポイントからプレイヤーに向かうベクトルを計算する。
		Vector3 diff = m_fortTop->GetPosition() - m_position;
		//プレイヤーから大砲移動の頂点ポイントに向かうベクトルを正規化する。
		diff.Normalize();
		//移動速度を計算する。
		m_moveSpeed = diff * FORTMOVE;
		//現在の移動速度を慣性速度に渡しておく。
		m_inertiaSpeed = m_moveSpeed;
		//エフェクトを再生する。
		DashEffect();
		//効果音を一度だけ再生する。
		if (Fort_Move_Se == true)
		{
			//効果音を設定する。
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->FORTMOVE);
			//ループ再生しない。
			se->Play(false);
			//ボリュームの設定。
			se->SetVolume(0.15f);
			Fort_Move_Se = false;
		}
	}
	//大砲移動で下降しているなら
	else if (Fort_Move == false && Fort_Top == true)
	{
		//大砲移動(空中)ステートに遷移する。
		m_playerState = enPlayerState_Fort_Air;
		//慣性速度に0.2fを乗算する。
		m_inertiaSpeed *= FORTINERTIAMULTIPLICATION;
		//重力をかける。
		m_inertiaSpeed.y -= GRAVITY;
		//慣性速度を現在の移動速度に渡す。
		m_moveSpeed += m_inertiaSpeed;
		//エフェクトを再生する。
		DashEffect();
		//プレイヤーが着地しているなら
		if (m_charaCon.IsOnGround())
		{
			//大砲移動(地上)ステートに遷移する。
			m_playerState = enPlayerState_Fort_Ground;
			//移動速度を計算する。
			m_moveSpeed += m_forward * FORTGROUNDMULTIPLICATION;
			//大砲移動(地上)出来る時間を加算する。
			m_fortTime += g_gameTime->GetFrameDeltaTime();
			////大砲移動(地上)出来る時間が0.4秒以上なら
			if (m_fortTime >= FORTTIMEMAX)
			{
				//大砲移動で降下する処理をしない。
				Fort_Top = false;
				//大砲移動(地上)出来る時間を初期化しておく。
				m_fortTime = ZERO;
			}
			//通常カメラ状態にする。
			Default = true;
			//中間地点に到達する。
			m_game->Try = true;
		}
	}
}
void Player::Move_Goal()
{
	//ゴール(ダンス)が出来るなら
	if (Goal2 == true)
	{
		//x.z方向の移動速度を0にする。
		m_moveSpeed.x = ZERO;
		m_moveSpeed.z = ZERO;
		//ゴール(ダンス)ステートに遷移する。
		m_playerState = enPlayerState_Goal2;
		return;
	}
	//着地していて
	if (m_charaCon.IsOnGround())
	{
		//ゴール状態なら
		if (Goal == true)
		{
			//x.z方向の移動速度を0にする。
			m_moveSpeed.x = ZERO;
			m_moveSpeed.z = ZERO;
			//ゴールポイントからプレイヤーに向かうベクトルを計算する。
			Vector3 diff = m_goal->GetPosition() - m_position;
			//プレイヤーからゴールポイントに向かうベクトルを正規化する。
			diff.Normalize();
			//移動速度を計算する。
			m_moveSpeed = diff * GOALMULTIPLICATION;
			//Y方向の移動速度を0にする。
			m_moveSpeed.y = ZERO;
			//ゴール(後転)ステートに遷移する。
			m_playerState = enPlayerState_Goal;
		}
	}
}
void Player::Move_Common()
{
	//ヒップドロップの着地硬直が終了していたら
	if (m_dropTime >= DROPTIMEMAX)
	{
		//移動エフェクトの再生開始時間を加算する。
		m_moveTime += g_gameTime->GetFrameDeltaTime();
		//移動エフェクトの再生開始時間が0.3秒以上なら
		if (m_moveTime > MOVEEFFECTTIMEMAX)
		{
			//ダッシュエフェクトを再生する。
			DashEffect();
		}
		//XかYボタンを押していて、ダッシュした時間が2秒以下なら
		if (g_pad[0]->IsPress(enButtonX) && m_dashTime < DASHTIMEMAX
			|| g_pad[0]->IsPress(enButtonY) && m_dashTime < DASHTIMEMAX)
		{
			//ダッシュステートに遷移する。
			m_playerState = enPlayerState_Dash;
			//スーパーダッシュ準備完了エフェクトを再生できるようにする。
			Dash_Max_Effect = true;
			//スーパーダッシュの火花、焦げ跡エフェクトを再生できるようにする。
			Dash_Max_Start_Effect = true;
			
		}
		//XかYボタンを押していて、ダッシュした時間が2秒以上なら
		else if (g_pad[0]->IsPress(enButtonX) && m_dashTime > DASHTIMEMAX
			|| g_pad[0]->IsPress(enButtonY) && m_dashTime > DASHTIMEMAX)
		{
			//スーパーダッシュステートに遷移する。
			m_playerState = enPlayerState_Dash_Max;
			
			//スーパーダッシュ準備完了エフェクトを再生できるなら
			if (Dash_Max_Effect == true)
			{
				//スーパーダッシュ準備完了エフェクトを再生する。
				Dash_MaxEffect();
				//効果音を設定する。
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(m_soundlist->DASHMAX);
				//ループ再生しない。
				se->Play(false);
				//ボリュームの設定。
				se->SetVolume(0.3f);
				Dash_Max_Effect = false;
			}
		}
		//ダッシュしていないなら
		else
		{
			//歩きステートに遷移する。
			m_playerState = enPlayerState_Walk;
			//歩きエフェクトを再生する。
			WalkEffect();
			//スーパーダッシュ準備完了エフェクトを再生できるようにする。
			Dash_Max_Effect = true;
		}
	}
}
void Player::Rotation()
{
		//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);

	}
	//絵描きさんに回転を教える。
	m_modelRender.SetRotation(m_rotation);
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}
void Player::Collision()
{
	//ヒップドロップ中、大砲移動中なら
	if (Drop == true||Fort_Idle==true||Fort_Move==true)
	{
		//処理しない。
		return;
	}
	//回転する地面のコリジョンを所得する。
	const auto& movecollision = g_collisionObjectManager->FindCollisionObjects("Move");
	//コリジョンの配列をfor文で回す。
	for (auto collision : movecollision)
	{
		//回転する地面のコリジョンと自身の当たり判定が衝突したら
		if (collision->IsHit(m_charaCon))
		{
			//プレイヤーが回転する地面に乗っていることにする。
			OnGroundMove = true;
		}
		//回転する地面のコリジョンと自身の当たり判定が衝突していないなら
		else if (!collision->IsHit(m_charaCon))
		{
			//プレイヤーが回転する地面に乗っていないことにする。
			OnGroundMove = false;
		}
	}
	//死亡するコリジョンを所得する。
	const auto& deadcollision = g_collisionObjectManager->FindCollisionObjects("Dead");
	//コリジョンの配列をfor文で回す。
	for (auto collision : deadcollision)
	{
		//死亡するコリジョンと自身の当たり判定が衝突したら
		if (collision->IsHit(m_charaCon))
		{
			//死亡状態にする。
			Dead = true;
			//死亡ステートに遷移する。
			m_playerState = enPlayerState_Dead;
		}
	}
	//ブロックのコリジョンを所得する。
	const auto& blockcollision = g_collisionObjectManager->FindCollisionObjects("Block");
	//コリジョンの配列をfor文で回す。
	for (auto collision : blockcollision)
	{
		//ブロックのコリジョンと自身の当たり判定が衝突したら
		if (collision->IsHit(m_charaCon))
		{
			//Y方向の移動速度を０にする。
			m_moveSpeed.y = ZERO;
			//重力を0にする。
			m_moveSpeed.y += GRAVITY;
			//ブロックの上に乗っている状態にする。
			OnBlock = true;
		}
		else
		{
			//ブロックの上に乗っていない状態にする。
			OnBlock = false;
		}
		//ブロックのコリジョンと自身の体のコリジョンが衝突したら
		if (collision->IsHit(m_collisionObject))
		{
			//x.z方向の移動速度を0にする。
			m_moveSpeed.x = ZERO;
			m_moveSpeed.z = ZERO;
			//当たり判定を削除する。
			m_charaCon.RemoveRigidBoby();
			//当たり判定を作成する。
			m_charaCon.Init(
				CHARACONHITBLOCK,//半径
				CHARACONHITBLOCK,//高さ
				m_position//座標
			);
			//プレイヤーがブロックの横から衝突している状態にする。
			HitBlock = true;
		}
	}
}
void Player::ProcessCommonStateTransition()
{
	//プレイヤーが操作できない状態なら
	if (Fort_Idle == true || Fort_Move == true || Fort_Top == true || Goal == true ||
		m_playerState == enPlayerState_Dead || m_playerState == enPlayerState_Fall)
	{
		//処理しない。
		return;
	}
	//ブロックの上に乗っていて、左スティックの操作がされているなら
	if (OnBlock == true&&Stick==true)
	{
		//移動ステートの処理を行う。
		Move_Common();
	}
	//左スティックの操作がされているなら
	else if (Stick == true)
	{
		//待機時間を0にする。
		m_idleTime = ZERO;
		//地上にいるなら
		if (m_charaCon.IsOnGround())
		{
			//移動ステートの処理を行う。
			Move_Common();
		}
	}
	//x.z方向の移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//待機ステートに遷移する。
		m_playerState = enPlayerState_Idle;
		//待機時間を加算する。
		m_idleTime += g_gameTime->GetFrameDeltaTime();
		//待機時間が6秒以上だったら。
		if (m_idleTime >= IDLETIMEMAX)
		{
			//放置中待機ステートに遷移する。
			m_playerState = enPlayerState_Idle2;
		}
	}
}
void Player::ProcessFortStateTransition()
{
	//アニメーションの再生が終了したら
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//共通のステートに遷移する。
		ProcessCommonStateTransition();
	}
}
void Player::ProcessJumpStateTransition()
{
	//アニメーションの再生が終了していて着地していたら
	if (m_modelRender.IsPlayingAnimation()== false ||
		m_charaCon.IsOnGround()||OnBlock==true)
	{
		//共通のステートに遷移する。
		ProcessCommonStateTransition();
	}
}
void Player::ProcessDropStateTransition()
{
	//着地していたら
	if (m_charaCon.IsOnGround())
	{
		//ヒップドロップ(落下)を処理しない。
		Drop = false;
		//ヒップドロップ(落下前)を処理しない。
		Stop = false;
		//共通のステートに遷移する。
		ProcessCommonStateTransition();
	}
}
void Player::ProcessGoalStateTransition()
{
	//アニメーションの再生が終了したら
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//ゴール(ダンス)を可能にする。
		Goal2 = true;
		//エフェクトを再生する。
		ClearEffect();
	}
}
void Player::ProcessGoal2StateTransition()
{
	//Aボタンを押していたら
	if (g_pad[0]->IsPress(enButtonA))
	{
		//ゴール後の処理を行う。
		m_game->Retry();
	}
	/*if (m_modelRender.IsPlayingAnimation() == false)
	{
		m_game->Retry();	
	}*/
}
void Player::ProcessDeadStateTransition()
{
	//アニメーションの再生が終了したら
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//自身を削除する。
		DeleteGO(this);
		//復活処理を一度だけ行う。
		if (ReTry == true)
		{
			//復活、ゲームオーバーの処理を行う。
			m_game->Retry();
			ReTry = false;
		}
	}
}
void Player::ManageState()
{
	switch (m_playerState)
	{
	//待機ステートの時。
	case enPlayerState_Idle:
		//共通のステートの遷移処理。
		ProcessCommonStateTransition();
		break;
	//放置中待機ステートの時。
	case enPlayerState_Idle2:
		//共通のステートの遷移処理。
		ProcessCommonStateTransition();
		break;
	//歩きステートの時。
	case enPlayerState_Walk:
		//共通のステートの遷移処理。
		ProcessCommonStateTransition();
		break;
	//ダッシュステートの時。
	case enPlayerState_Dash:
		//共通のステートの遷移処理。
		ProcessCommonStateTransition();
		break;
	//スーパーダッシュステートの時。
	case enPlayerState_Dash_Max:
		//共通のステートの遷移処理。
		ProcessCommonStateTransition();
		break;
	//ジャンプステートの時。
	case enPlayerState_Jump:
		//ジャンプステートの遷移処理。
		ProcessJumpStateTransition();
		break;
	//ヒップドロップステートの時。
	case enPlayerState_Drop:
		//ヒップドロップステートの遷移処理。
		ProcessDropStateTransition();
		break;
	//大砲移動(地上)ステートの時。
	case enPlayerState_Fort_Ground:
	    //大砲移動(地上)ステートの遷移処理。
		ProcessFortStateTransition();
		break;
	//大砲移動(空中)ステートの時。
	case enPlayerState_Fort_Air:
		//共通のステートの遷移処理。
		ProcessCommonStateTransition();
		break;
	//ゴール(後転)ステートの時
	case enPlayerState_Goal:
		//ゴール(後転)ステートの遷移処理。
		ProcessGoalStateTransition();
		break;
	//ゴール(ダンス)ステートの時。
	case enPlayerState_Goal2:
		//ゴール(ダンス)ステートの遷移処理。
		ProcessGoal2StateTransition();
		break; 
	//死亡ステートの時。
	case enPlayerState_Dead:
		//死亡ステートの遷移処理。
		ProcessDeadStateTransition();
		break;
	//落下ステートの時。
	case enPlayerState_Fall:
		//死亡ステートの遷移処理。
		ProcessDeadStateTransition();
		break;
	}
}
void Player::PlayAnimation()
{
	//アニメーションの再生速度。
	m_modelRender.SetAnimationSpeed(1.0f);
	////switch文。
	switch (m_playerState) {
	//待機ステートの時。
	case enPlayerState_Idle:
		//待機アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.8f);
		break;
	//放置中待機ステートの時。
	case enPlayerState_Idle2:
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.1f);
		//放置中待機アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Idle2, 0.9f);
		break;
	//歩きステートの時。
	case enPlayerState_Walk:
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.5f);
		//歩きアニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Walk, 0.8f);
		break;
	//ダッシュステートの時。
	case enPlayerState_Dash:
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.2f);
		//ダッシュアニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Dash, 0.8f);
		break;
	//スーパーダッシュステートの時。
	case enPlayerState_Dash_Max:
		//スーパーダッシュアニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Dash_Max, 0.8f);
		break;
	//ジャンプステートの時。
	case enPlayerState_Jump:
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(1.1f);
		//ジャンプアニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Jump, 1.0f);
		break;
	//ヒップドロップステートの時。
	case enPlayerState_Drop:
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(0.8f);
		//ヒップドロップアニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Drop, 1.0f);
		break;
	//大砲移動(地上)ステートの時。
	case enPlayerState_Fort_Ground:
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(0.9f);
		//大砲移動(地上)アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Fort_Ground, 1.0f);
		break;
	//大砲移動(空中)ステートの時。
	case enPlayerState_Fort_Air:
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(0.9f);
		//大砲移動(空中)アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Fort_Air, 1.0f);
		break;
	//ゴール(後転)ステートの時。
	case enPlayerState_Goal:
		//ゴール(後転)アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Goal, 1.0f);
		break;
	//ゴール(ダンス)ステートの時。
	case enPlayerState_Goal2:
		//ゴール(ダンス)アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Goal2, 1.0f);
		break;
	//死亡ステートの時。
	case enPlayerState_Dead:
		//アニメーションの再生速度。
		m_modelRender.SetAnimationSpeed(0.8f);
		//死亡アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Dead, 1.0f);
		break;
	//落下ステートの時。
	case enPlayerState_Fall:
		//落下アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Fall, 1.0f);
		break;
	default:
		break;
	}
}
void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//キーの名前が「Jump_Start」の時。
	if (wcscmp(eventName, L"Jump_Start") == 0)
	{
		//重力をジャンプ上昇時重力にする。
		Gravity = false;
		//エフェクトを再生する。
		JumpEffect();
	}
	//キーの名前が「Jump_End」の時。
	else if (wcscmp(eventName, L"Jump_end") == 0)
	{
		//重力を通常にする。
		Gravity = true;
	}
	//キーの名前が「Drop_Start」の時。
	else if (wcscmp(eventName, L"Drop_Start") == 0)
	{
		//ヒップドロップ準備中にする。
		Stop = true;
	}
	//キーの名前が「Drop_End」の時。
	else if (wcscmp(eventName, L"Drop_End") == 0)
	{
		//ヒップドロップ準備中の処理しない。。
		Stop = false;
		//ヒップドロップ中にする。
		Drop = true;
		//強い重力を与える。
		m_moveSpeed.y = -DROPGRAVITY;
	}
	//キーの名前が「Dash」の時。
	else if (wcscmp(eventName, L"Dash") == 0)
	{
		//効果音を設定する。
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(m_soundlist->DASH);
		//ループ再生しない。
		se->Play(false);
		//ボリュームの設定。
		se->SetVolume(0.2f);
	}
	//キーの名前が「Walk」の時。
	else if (wcscmp(eventName, L"Walk") == 0)
	{
		//効果音を設定する。
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(m_soundlist->WALK);
		//ループ再生しない。
		se->Play(false);
		//ボリュームの設定。
		se->SetVolume(0.4f);
	}
	//キーの名前が「Dash_Max_Start」の時。
	else if (wcscmp(eventName, L"Dash_Max_Start") == 0)
	{ 
		//スーパーダッシュの火花、焦げ跡のエフェクトを一度だけ再生する。
		if (Dash_Max_Start_Effect == true)
		{
			//スーパーダッシュの火花のエフェクトを再生する。
			Dash_Max_FirstEffect();
			//スーパーダッシュの焦げ跡のエフェクトを再生する。
			Dash_Max_First2Effect();
			Dash_Max_Start_Effect = false;
			//効果音を設定する。
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->DASHFIRST);
			//ループ再生しない。
			se->Play(false);
			//ボリュームの設定。
			se->SetVolume(0.6f);
		}
		else
		{
			//効果音を設定する。
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(m_soundlist->DMM);
			//ループ再生しない。
			se->Play(false);
			//ボリュームの設定。
			se->SetVolume(0.08f);
		}
	}
}
void Player::Render(RenderContext& rc)
{
	//プレイヤーを描画するなら
	if (PlayerNotDraw == false)
	{
		//モデルを描画する。
		m_modelRender.Draw(rc);
	}
	//UI表示開始時間が2秒以上なら
	if (m_UITime > UITIMEMAX)
	{
		//キャラクターアイコン画像を描画する。
		m_aiconSprite.Draw(rc);
		//制限時間画像を描画する。
		m_timerSprite.Draw(rc);
		//制限時間フォントを描画する。
		m_timeLimitFont.Draw(rc);
		//HPフォントを描画する。
		m_hpCountFont.Draw(rc);
	}
	//ゴール状態なら
	if (Goal == true)
	{
		//クリア画像を描画する。
		m_clear.Draw(rc);
	}
}
void Player::InitAnimation()
{
	//アニメーションを読み込む。
	m_animClips[enAnimationClip_Idle].Load("Assets/animData/Player_Idle.tka");
	m_animClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_Idle2].Load("Assets/animData/Player_Idle2.tka");
	m_animClips[enAnimationClip_Idle2].SetLoopFlag(true);
	m_animClips[enAnimationClip_Walk].Load("Assets/animData/Player_Walk.tka");
	m_animClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_Dash].Load("Assets/animData/Player_Dash.tka");
	m_animClips[enAnimationClip_Dash].SetLoopFlag(true);
	m_animClips[enAnimationClip_Dash_Max].Load("Assets/animData/Player_Dash_Max.tka");
	m_animClips[enAnimationClip_Dash_Max].SetLoopFlag(true);
	m_animClips[enAnimationClip_Jump].Load("Assets/animData/Player_Jump.tka");
	m_animClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animClips[enAnimationClip_Drop].Load("Assets/animData/Player_HipDrop.tka");
	m_animClips[enAnimationClip_Drop].SetLoopFlag(false);
	m_animClips[enAnimationClip_Fort_Ground].Load("Assets/animData/Player_Fort_Ground.tka");
	m_animClips[enAnimationClip_Fort_Ground].SetLoopFlag(false);
	m_animClips[enAnimationClip_Fort_Air].Load("Assets/animData/Player_Fort_Air.tka");
	m_animClips[enAnimationClip_Fort_Air].SetLoopFlag(true);
	m_animClips[enAnimationClip_Goal].Load("Assets/animData/Player_Goal.tka");
	m_animClips[enAnimationClip_Goal].SetLoopFlag(false);
	m_animClips[enAnimationClip_Goal2].Load("Assets/animData/Player_Goal2.tka");
	m_animClips[enAnimationClip_Goal2].SetLoopFlag(true);
	m_animClips[enAnimationClip_Dead].Load("Assets/animData/Player_Dead.tka");
	m_animClips[enAnimationClip_Dead].SetLoopFlag(false);
	m_animClips[enAnimationClip_Fall].Load("Assets/animData/Player_Fall.tka");
	m_animClips[enAnimationClip_Fall].SetLoopFlag(false);
}
void Player::InitSprite()
{
	/// <summary>
	/// キャラクターアイコン
	/// </summary>
	//キャラクターアイコン画像を読み込む。
	m_aiconSprite.Init("Assets/sprite/aicon.DDS", 200, 200);
	//ピボットを設定する。
	m_aiconSprite.SetPivot(Vector2(ATCSPRITEPIVOT));
	//座標を設定する。
	m_aiconSprite.SetPosition(Vector3(AICONSPRITEPOS));
	//更新処理。
	m_aiconSprite.Update();
	/// <summary>
	/// 制限時間画像
	/// </summary>
	//制限時間画像を読み込む。
	m_timerSprite.Init("Assets/sprite/timer.DDS", 80, 80);
	//ピボットを設定する。
	m_timerSprite.SetPivot(Vector2(ATCSPRITEPIVOT));
	//座標を設定する。
	m_timerSprite.SetPosition(Vector3(TIMERSPRITEPOS));
	//更新処理。
	m_timerSprite.Update();
	/// <summary>
	/// クリア画像
	/// </summary>
	//クリア画像を読み込む。
	m_clear.Init("Assets/sprite/clear.DDS", 1000, 1100);
	//ピボットを設定する。
	m_clear.SetPivot(Vector2(ATCSPRITEPIVOT));
	//座標を設定する。
	m_clear.SetPosition(Vector3(CLEARSPRITEPOS));
	//更新処理。
	m_clear.Update();
}
void Player::HP()
{
	//現在のHPを表示する。
	m_hpCountwst = std::to_wstring(m_game->HP);
	m_hpCountFont.SetText(m_hpCountwst.c_str());
	//座標を設定する。
	m_hpCountFont.SetPosition(HPFONTPOS);
	//ピボットを設定する。
	m_hpCountFont.SetPivot(Vector2(HPFONTPIVOT));
	//大きさを設定する。
	m_hpCountFont.SetScale(HPFONTSCALE);
	//影のパラメーターを設定する。
	m_hpCountFont.SetShadowParam(true, HPFONTOFFSET, g_vec4White);
	//HPが1なら
	if (m_game->HP <= HPFONTCOLORRED)
	{
		//文字を赤にする。
		m_hpCountFont.SetColor(g_vec4Red);
	}
	//HPが3以下なら
	else if (m_game->HP <= HPFONTCOLORYELLOW)
	{
		//文字を黄色にする。
		m_hpCountFont.SetColor(g_vec4Yellow);
	}
	//HPが５以下なら
	else {
		//文字を白にする。
		m_hpCountFont.SetColor(g_vec4Gray);
	}
}
void Player::TimeLimit()
{
	//制限時間をint型にする。
	Game_Timer = m_game->m_gameTime;
	//現在の制限時間を表示する。
	m_timeLimittwst = std::to_wstring(Game_Timer);
	m_timeLimitFont.SetText(m_timeLimittwst.c_str());
	//座標を設定する。
	m_timeLimitFont.SetPosition(TIMEFONTPOS);
	//ピボットを設定する。
	m_timeLimitFont.SetPivot(Vector2(TIMEFONTPIVOT));
	//大きさを設定する。
	m_timeLimitFont.SetScale(TIMEFONTSCALE);
	//影のパラメーターを設定する。
	m_timeLimitFont.SetShadowParam(true, TIMEFONTOFFSET, g_vec4White);
	//制限時間が30秒以下なら
	if (Game_Timer <= TIMEFONTCOLORRED)
	{
		//文字を赤にする。
		m_timeLimitFont.SetColor(g_vec4Red);
	}
	//制限時間が100秒以下なら
	else if (Game_Timer <= TIMEFONTCOLORYELLOW)
	{
		//文字をオレンジ色にする。
		m_timeLimitFont.SetColor(g_vec4Orange);
	}
	//制限時間が300秒以下なら
	else {
		//文字を白にする。
		m_timeLimitFont.SetColor(g_vec4Gray);
	}
}
void Player::DashEffect()
{
	//エフェクトのオブジェクトを作成する。
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->MOVE);
	//座標を設定する。
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//回転を設定する。
	m_effectEmitter->SetRotation(m_rotation);
	//大きさを設定する。
	m_effectEmitter->SetScale(WALKDASHEFFECTSCALE);
	//エフェクトを再生する。
	m_effectEmitter->Play();
}
void Player::WalkEffect()
{
	//エフェクトのオブジェクトを作成する。
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->WALK);
	//座標を設定する。
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//回転を設定する。
	m_effectEmitter->SetRotation(m_rotation);
	//大きさを設定する。
	m_effectEmitter->SetScale(WALKDASHEFFECTSCALE);
	//エフェクトを再生する。
	m_effectEmitter->Play();
}
void Player::Dash_MaxEffect()
{
	//エフェクトのオブジェクトを作成する。
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->DASHFIRST);
	//座標を設定する。
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//回転を設定する。
	m_effectEmitter->SetRotation(m_rotation);
	//大きさを設定する。
	m_effectEmitter->SetScale(WALKDASHEFFECTSCALE);
	//エフェクトを再生する。
	m_effectEmitter->Play();
}
void Player::Dash_Max_FirstEffect()
{
	//エフェクトのオブジェクトを作成する。
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->DMF);
	//座標を設定する。
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//回転を設定する。
	m_effectEmitter->SetRotation(m_rotation);
	//大きさを設定する。
	m_effectEmitter->SetScale(DMFEFFECTSCALE);
	//エフェクトを再生する。
	m_effectEmitter->Play();
}
void Player::Dash_Max_First2Effect()
{
	//エフェクトのオブジェクトを作成する。
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->DMF2);
	//座標を設定する。
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//回転を設定する。
	m_effectEmitter->SetRotation(m_rotation);
	//大きさを設定する。
	m_effectEmitter->SetScale(DMF2EFFECTSCALE);
	//エフェクトを再生する。
	m_effectEmitter->Play();
}
void Player::JumpEffect()
{
	//エフェクトのオブジェクトを作成する。
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->JUMP);
	//座標を設定する。
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//回転を設定する。
	m_effectEmitter->SetRotation(m_rotation);
	//大きさを設定する。
	m_effectEmitter->SetScale(JUMPEFFECTSCALE);
	m_effectEmitter->Play();
}
void Player::Drop_EndEffect()
{
	//エフェクトのオブジェクトを作成する。
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->DROP);
	//座標を設定する。
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//回転を設定する。
	m_effectEmitter->SetRotation(m_rotation);
	//大きさを設定する。
	m_effectEmitter->SetScale(DROPEFFECTSCALE);
	//エフェクトを再生する。
	m_effectEmitter->Play();
}
void Player::ClearEffect()
{
	//エフェクトのオブジェクトを作成する。
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(m_effectlist->CLEAR);
	//座標を設定する。
	Vector3 effectPosition = m_position;
	m_effectEmitter->SetPosition(effectPosition);
	//回転を設定する。
	m_effectEmitter->SetRotation(m_rotation);
	//大きさを設定する。
	m_effectEmitter->SetScale(CLEAREFFECTSCALE);
	//エフェクトを再生する。
	m_effectEmitter->Play();
}
void Player::HedCollision() 
{
	//コリジョンオブジェクトを作成する。
	auto Hedcollision = NewGO<CollisionObject>(0);
	//座標を設定する。
	Vector3 m_boxposition = m_position;
	m_boxposition.y = m_position.y + HEDCOLLISIONPOSY;
	//ボックス状のコリジョンを作成する。
	Hedcollision->CreateBox(
		m_boxposition,//座標
		Quaternion::Identity,//回転
		HEDCOLLISIONSCALE//大きさ
	);
	//名前をHeadにする。
	Hedcollision->SetName("Head");
}
void Player::LegCollision()
{
	//コリジョンオブジェクトを作成する。
	auto Legcollision = NewGO<CollisionObject>(0);
	//座標を設定する。
	Vector3 m_boxposition = m_position;
	m_boxposition.y = m_position.y - LEGCOLLISIONPOSY;
	//ボックス状のコリジョンを作成する。
	Legcollision->CreateBox(
		m_boxposition,//座標。
		Quaternion::Identity,//回転
		LEGCOLLISIONSCALE//大きさ
	);
	//名前をLegにする。
	Legcollision->SetName("Leg");
}
void Player::HipCollision()
{
	//コリジョンオブジェクトを作成する。
	auto HipCollision = NewGO<CollisionObject>(0);
	//座標を設定する。
	Vector3 m_boxposition = m_position;
	m_boxposition.y = m_position.y - HIPCOLLISIONPOSY;
	//ボックス状のコリジョンを作成する。
	HipCollision->CreateBox(
		m_boxposition,
		Quaternion::Identity,
		HIPCOLLISIONSCALE);
	//名前をHipにする。
	HipCollision->SetName("Hip");
}