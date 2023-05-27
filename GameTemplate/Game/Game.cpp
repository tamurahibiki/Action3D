#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Ground.h"
#include "Tree.h"
#include "Fence.h"
#include "FenceHalf.h"
#include "Stairs.h"
#include "Block.h"
#include "FlowerBed.h"
#include "WoodenBox.h"
#include "Grass.h"
#include "Flower.h"
#include "Shrub.h"
#include "Pebble.h"
#include "Signboard.h"
#include "Wood_Road.h"
#include "Windmill.h"
#include "Pipe.h"
#include "Rock_Big.h"
#include "GroundMove.h"
#include "GroundRoad.h"
#include "Fort.h"
#include "FortTop.h"
#include "Ring.h"
#include "Bard.h"
#include "Enemy_Green.h"
#include "Enemy_Red.h"
#include "Enemy_Yellow.h"
#include "GoalPoint.h"
#include "GameCamera.h"
#include "HitBox.h"
#include "Default.h"
#include "Forward.h"
#include "SkyCube.h"
#include "Fade.h"
#include "Title.h"
#include "EffectList.h"
#include "SoundList.h"

namespace
{
	const int ZERO = 0;//ゼロ
}
namespace App {
	Game::Game() {}
	Game::~Game()
	{
		//////////////////////////////////////
		//ここからプレイヤーの位置情報が必要でないオブジェクトを削除する。
		//////////////////////////////////////
		DeleteGO(m_sky);
		DeleteGO(FindGO<Ground>("ground"));
		DeleteGO(FindGO<GroundRoad>("groundroad"));
		DeleteGO(FindGO<GroundMove>("groundmove"));
		DeleteGO(FindGO<Stairs>("stairs"));
		DeleteGO(FindGO<Windmill>("windmill"));
		const auto& blocks = FindGOs<Block>("block");
		for (auto block : blocks)
		{
			DeleteGO(block);
		}
		const auto& shrubs = FindGOs<Shrub>("shrub");
		for (auto shrub : shrubs)
		{
			DeleteGO(shrub);
		}
		const auto& pebbles = FindGOs<Pebble>("pebble");
		for (auto pebble : pebbles)
		{
			DeleteGO(pebble);
		}
		const auto& pipes = FindGOs<Pipe>("pipe");
		for (auto pipe : pipes)
		{
			DeleteGO(pipe);
		}
		const auto& fences = FindGOs<Fence>("fence");
		for (auto fence : fences)
		{
			DeleteGO(fence);
		}
		const auto& fencehalfs = FindGOs<FenceHalf>("fencehalf");
		for (auto fencehalf : fencehalfs)
		{
			DeleteGO(fencehalf);
		}
		const auto& flowers = FindGOs<Flower>("flower");
		for (auto flower : flowers)
		{
			DeleteGO(flower);
		}
		const auto& flowerbeds = FindGOs<FlowerBed>("flowerbed");
		for (auto flowerbed : flowerbeds)
		{
			DeleteGO(flowerbed);
		}
		const auto& grasses = FindGOs<Grass>("grass");
		for (auto grass : grasses)
		{
			DeleteGO(grass);
		}
		const auto& hitboxs = FindGOs<HitBox>("hitbox");
		for (auto hitbox : hitboxs)
		{
			DeleteGO(hitbox);
		}
		const auto& rock_bigs = FindGOs<Rock_Big>("rock_big");
		for (auto rock_big : rock_bigs)
		{
			DeleteGO(rock_big);
		}
		const auto& rings = FindGOs<Ring>("ring");
		for (auto ring : rings)
		{
			DeleteGO(ring);
		}
		const auto& signboards = FindGOs<Signboard>("signboard");
		for (auto signboard : signboards)
		{
			DeleteGO(signboard);
		}
		const auto& trees = FindGOs<Tree>("tree");
		for (auto tree : trees)
		{
			DeleteGO(tree);
		}
		const auto& wood_roads = FindGOs<Wood_Road>("wood_road");
		for (auto wood_road : wood_roads)
		{
			DeleteGO(wood_road);
		}
		const auto& woodenboxs = FindGOs<WoodenBox>("woodenbox");
		for (auto woodenbox : woodenboxs)
		{
			DeleteGO(woodenbox);
		}
		//////////////////////////////////////
		//プレイヤーの位置情報が必要でないオブジェクトを削除するのはここまで。
		//////////////////////////////////////
		//BGMを削除する。
		DeleteGO(m_bgm);
	}
	bool Game::Start()
	{
		//空のオブジェクトを作成する。
		m_sky = NewGO<SkyCube>(0, "sky");
		//プレイヤーのオブジェクトを作成する。
		m_player = NewGO<Player>(0, "player");
		//レベルを構築する。
		m_levelRender.Init("Assets/level3D/level1.tkl",
			[&](LevelObjectData& objData) {
				//名前がgroundだったら
				if (objData.EqualObjectName(L"ground") == true) {
					//地形のオブジェクトを作成する。
					Ground* bg = NewGO<Ground>(0, "ground");
					//座標を設定する。
					bg->SetPosition(objData.position);
					//大きさを設定する。
					bg->SetScale(objData.scale);
					//回転を設定する。
					bg->SetRotation(objData.rotation);
					return true;
				}
				//名前がgroundmoveだったら
				else if (objData.EqualObjectName(L"groundmove") == true) {
					//回転する地面のオブジェクトを作成する。
					GroundMove* groundmove = NewGO<GroundMove>(0, "groundmove");
					//座標を設定する。
					groundmove->SetPosition(objData.position);
					//大きさを設定する。
					groundmove->SetScale(objData.scale);
					//回転を設定する。
					groundmove->SetRotation(objData.rotation);
					return true;
				}
				//名前がtreeだったら
				else if (objData.EqualObjectName(L"tree") == true) {
					//木のオブジェクトを作成する。
					Tree* tree = NewGO<Tree>(0, "tree");
					//座標を設定する。
					tree->SetPosition(objData.position);
					//大きさを設定する。
					tree->SetScale(objData.scale);
					//回転を設定する。
					tree->SetRotation(objData.rotation);
					return true;
				}
				//名前がshrubだったら
				else if (objData.EqualObjectName(L"shrub") == true) {
					//低木のオブジェクトを作成する。
					Shrub* shrub = NewGO<Shrub>(0, "shrub");
					//座標を設定する。
					shrub->SetPosition(objData.position);
					//大きさを設定する。
					shrub->SetScale(objData.scale);
					//回転を設定する。
					shrub->SetRotation(objData.rotation);
					return true;
				}
				//名前がgrassだったら
				else if (objData.EqualObjectName(L"grass") == true) {
					//草のオブジェクトを作成する。
					Grass* grass = NewGO<Grass>(0, "grass");
					//座標を設定する。
					grass->SetPosition(objData.position);
					//大きさを設定する。
					grass->SetScale(objData.scale);
					//回転を設定する。
					grass->SetRotation(objData.rotation);
					return true;
				}
				//名前がflowerだったら
				else if (objData.EqualObjectName(L"flower") == true) {
					//花のオブジェクトを作成する。
					Flower* flower = NewGO<Flower>(0, "flower");
					//座標を設定する。
					flower->SetPosition(objData.position);
					//大きさを設定する。
					flower->SetScale(objData.scale);
					//回転を設定する。
					flower->SetRotation(objData.rotation);
					return true;
				}
				//名前がflowerbedだったら
				else if (objData.EqualObjectName(L"flowerbed") == true) {
					//花壇のオブジェクトを作成する。
					FlowerBed* flowerbed = NewGO<FlowerBed>(0, "flowerbed");
					//座標を設定する。
					flowerbed->SetPosition(objData.position);
					//大きさを設定する。
					flowerbed->SetScale(objData.scale);
					//回転を設定する。
					flowerbed->SetRotation(objData.rotation);
					return true;
				}
				//名前がpebbleだったら
				else if (objData.EqualObjectName(L"pebble") == true) {
					//小石のオブジェクトを作成する。
					Pebble* pebble = NewGO<Pebble>(0, "pebble");
					//座標を設定する。
					pebble->SetPosition(objData.position);
					//大きさを設定する。
					pebble->SetScale(objData.scale);
					//回転を設定する。
					pebble->SetRotation(objData.rotation);
					return true;
				}
				//名前がrock_bigだったら
				else if (objData.EqualObjectName(L"rock_big") == true) {
					//大きな石のオブジェクトを作成する。
					Rock_Big* rock_big = NewGO<Rock_Big>(0, "rock_big");
					//座標を設定する。
					rock_big->SetPosition(objData.position);
					//大きさを設定する。
					rock_big->SetScale(objData.scale);
					//回転を設定する。
					rock_big->SetRotation(objData.rotation);
					return true;
				}
				//名前がfenceだったら
				else if (objData.EqualObjectName(L"fence") == true) {
					//フェンスのオブジェクトを作成する。
					Fence* fence = NewGO<Fence>(0, "fence");
					//座標を設定する。
					fence->SetPosition(objData.position);
					//大きさを設定する。
					fence->SetScale(objData.scale);
					//回転を設定する。
					fence->SetRotation(objData.rotation);
					return true;
				}
				//名前がfencehalfだったら
				else if (objData.EqualObjectName(L"fencehalf") == true) {
					//ハーフフェンスのオブジェクトを作成する。
					FenceHalf* fencehalf = NewGO<FenceHalf>(0, "fencehalf");
					//座標を設定する。
					fencehalf->SetPosition(objData.position);
					//大きさを設定する。
					fencehalf->SetScale(objData.scale);
					//回転を設定する。
					fencehalf->SetRotation(objData.rotation);
					return true;
				}
				//名前がstairsだったら
				else if (objData.EqualObjectName(L"stairs") == true) {
					//階段のオブジェクトを作成する。
					Stairs* stairs = NewGO<Stairs>(0, "stairs");
					//座標を設定する。
					stairs->SetPosition(objData.position);
					//大きさを設定する。
					stairs->SetScale(objData.scale);
					//回転を設定する。
					stairs->SetRotation(objData.rotation);
					return true;
				}
				//名前がsignboardだったら
				else if (objData.EqualObjectName(L"signboard") == true) {
					//看板のオブジェクトを作成する。
					Signboard* signboard = NewGO<Signboard>(0, "signboard");
					//座標を設定する。
					signboard->SetPosition(objData.position);
					//大きさを設定する。
					signboard->SetScale(objData.scale);
					//回転を設定する。
					signboard->SetRotation(objData.rotation);
					return true;
				}
				//名前がpipeだったら
				else if (objData.EqualObjectName(L"pipe") == true) {
					//土管のオブジェクトを作成する。
					Pipe* pipe = NewGO<Pipe>(0, "pipe");
					//座標を設定する。
					pipe->SetPosition(objData.position);
					//大きさを設定する。
					pipe->SetScale(objData.scale);
					//回転を設定する。
					pipe->SetRotation(objData.rotation);
					return true;
				}
				//名前がwoodenboxだったら
				else if (objData.EqualObjectName(L"woodenbox") == true) {
					//木箱のオブジェクトを作成する。
					WoodenBox* woodenbox = NewGO<WoodenBox>(0, "woodenbox");
					//座標を設定する。
					woodenbox->SetPosition(objData.position);
					//大きさを設定する。
					woodenbox->SetScale(objData.scale);
					//回転を設定する。
					woodenbox->SetRotation(objData.rotation);
					return true;
				}
				//名前がwood_roadだったら
				else if (objData.EqualObjectName(L"wood_road") == true) {
					//木製の道のオブジェクトを作成する。
					Wood_Road* wood_road = NewGO<Wood_Road>(0, "wood_road");
					//座標を設定する。
					wood_road->SetPosition(objData.position);
					//大きさを設定する。
					wood_road->SetScale(objData.scale);
					//回転を設定する。
					wood_road->SetRotation(objData.rotation);
					return true;
				}
				//名前がwindmillだったら
				else if (objData.EqualObjectName(L"windmill") == true) {
					//風車のオブジェクトを作成する。
					Windmill* windmill = NewGO<Windmill>(0, "windmill");
					//座標を設定する。
					windmill->SetPosition(objData.position);
					//大きさを設定する。
					windmill->SetScale(objData.scale);
					//回転を設定する。
					windmill->SetRotation(objData.rotation);
					return true;
				}
				//名前がblockだったら
				else if (objData.EqualObjectName(L"block") == true) {
					//ブロックのオブジェクトを作成する。
					Block* block = NewGO<Block>(0, "block");
					//座標を設定する。
					block->SetPosition(objData.position);
					//大きさを設定する。
					block->SetScale(objData.scale);
					//回転を設定する。
					block->SetRotation(objData.rotation);
					return true;
				}
				//名前がgoalpointだったら
				else if (objData.EqualObjectName(L"goalpoint") == true) {
					//ゴールポイントのオブジェクトを作成する。
					GoalPoint* goalpoint = NewGO<GoalPoint>(0, "goalpoint");
					//座標を設定する。
					goalpoint->SetPosition(objData.position);
					//大きさを設定する。
					goalpoint->SetScale(objData.scale);
					//回転を設定する。
					goalpoint->SetRotation(objData.rotation);
					return true;
				}
				//名前がfortだったら
				else if (objData.EqualObjectName(L"fort") == true) {
					//大砲のオブジェクトを作成する。
					Fort* fort = NewGO<Fort>(0, "fort");
					//座標を設定する。
					fort->SetPosition(objData.position);
					//大きさを設定する。
					fort->SetScale(objData.scale);
					//回転を設定する。
					fort->SetRotation(objData.rotation);
					return true;
				}
				//名前がforttopだったら
				else if (objData.EqualObjectName(L"forttop") == true) {
					//大砲移動の頂点ポイントのオブジェクトを作成する。
					FortTop* forttop = NewGO<FortTop>(0, "forttop");
					//座標を設定する。
					forttop->SetPosition(objData.position);
					//大きさを設定する。
					forttop->SetScale(objData.scale);
					//回転を設定する。
					forttop->SetRotation(objData.rotation);
					return true;
				}
				//名前がgroundroadだったら
				else if (objData.EqualObjectName(L"groundroad") == true) {
					//大砲周りの装飾のオブジェクトを作成する。
					GroundRoad* groundroad = NewGO<GroundRoad>(0, "groundroad");
					//座標を設定する。
					groundroad->SetPosition(objData.position);
					//大きさを設定する。
					groundroad->SetScale(objData.scale);
					//回転を設定する。
					groundroad->SetRotation(objData.rotation);
					return true;
				}
				//名前がringだったら
				else if (objData.EqualObjectName(L"ring") == true) {
					//リングのオブジェクトを作成する。
					Ring* ring = NewGO<Ring>(0, "ring");
					//座標を設定する。
					ring->SetPosition(objData.position);
					//大きさを設定する。
					ring->SetScale(objData.scale);
					//回転を設定する。
					ring->SetRotation(objData.rotation);
					return true;
				}
				//名前がbardだったら
				else if (objData.EqualObjectName(L"bard") == true) {
					//鳥のオブジェクトを作成する。
					Bard* bard = NewGO<Bard>(0, "bard");
					//座標を設定する。
					bard->SetPosition(objData.position);
					//大きさを設定する。
					bard->SetScale(objData.scale);
					//回転を設定する。
					bard->SetRotation(objData.rotation);
					return true;
				}
				//名前がenemy_greenだったら
				else if (objData.EqualObjectName(L"enemy_green") == true) {
					//遠距離攻撃エネミーのオブジェクトを作成する。
					Enemy_Green* enemy_green = NewGO<Enemy_Green>(0, "enemy_green");
					//座標を設定する。
					enemy_green->SetPosition(objData.position);
					//大きさを設定する。
					enemy_green->SetScale(objData.scale);
					//回転を設定する。
					enemy_green->SetRotation(objData.rotation);
					return true;
				}
				//名前がenemy_redだったら
				else if (objData.EqualObjectName(L"enemy_red") == true) {
					//追いかけてくるエネミーのオブジェクトを作成する。
					Enemy_Red* enemy_red = NewGO<Enemy_Red>(0, "enemy_red");
					//座標を設定する。
					enemy_red->SetPosition(objData.position);
					//大きさを設定する。
					enemy_red->SetScale(objData.scale);
					//回転を設定する。
					enemy_red->SetRotation(objData.rotation);
					return true;
				}
				//名前がenemy_yellowだったら
				else if (objData.EqualObjectName(L"enemy_yellow") == true) {
					//飛んでいるエネミーのオブジェクトを作成する。
					Enemy_Yellow* enemy_yellow = NewGO<Enemy_Yellow>(0, "enemy_yellow");
					//座標を設定する。
					enemy_yellow->SetPosition(objData.position);
					//大きさを設定する。
					enemy_yellow->SetScale(objData.scale);
					//回転を設定する。
					enemy_yellow->SetRotation(objData.rotation);
					return true;
				}
				//名前がhitboxだったら
				else if (objData.EqualObjectName(L"hitbox") == true) {
					//見えない当たり判定のオブジェクトを作成する。
					HitBox* hitbox = NewGO<HitBox>(0, "hitbox");
					//座標を設定する。
					hitbox->SetPosition(objData.position);
					//大きさを設定する。
					hitbox->SetScale(objData.scale);
					//回転を設定する。
					hitbox->SetRotation(objData.rotation);
					return true;
				}
				//名前がdefaultだったら
				else if (objData.EqualObjectName(L"default") == true) {
					//通常カメラに変更するポイントのオブジェクトを作成する。
					Default* defaultd = NewGO<Default>(0, "default");
					//座標を設定する。
					defaultd->SetPosition(objData.position);
					//大きさを設定する。
					defaultd->SetScale(objData.scale);
					//回転を設定する。
					defaultd->SetRotation(objData.rotation);
					return true;
				}
				//名前がforwardだったら
				else if (objData.EqualObjectName(L"forward") == true) {
					//奥行きカメラに変更するポイントのオブジェクトを作成する。
					Forward* forward = NewGO<Forward>(0, "forward");
					//座標を設定する。
					forward->SetPosition(objData.position);
					//大きさを設定する。
					forward->SetScale(objData.scale);
					//回転を設定する。
					forward->SetRotation(objData.rotation);
					return true;
				}
				return true;
			});
		//エフェクトを読み込む。
		m_effectlist = NewGO<EffectList>(0, "effectlist");
		//音を読み込む。
		m_soundlist = FindGO<SoundList>("soundlist");

		//BGMを再生する。
		m_bgm = NewGO<SoundSource>(0);
		m_bgm->Init(m_soundlist->GAMEBGM);
		//ループする。
		m_bgm->Play(true);
		//ボリュームを設定する。
		m_bgm->SetVolume(0.04f);

		m_fade = FindGO<Fade>("fade");
		m_fade->StartFadeIn();

		return true;
	}
	void Game::Update()
	{
		//m_player->RainEffect();
		//もしフェードアウト中なら
		if (m_isWaitFadeout)
		{
			//フェード中でないなら
			if (!m_fade->IsFade())
			{
				//フェードインする。
				m_fade->StartFadeIn();
			}
		}
		//制限時間の処理
		/*プレイヤーの状態が死亡していなくて、ゴールしていなくて、
		UIが表示されているなら*/
		if (m_player->Dead == false && m_player->Goal == false
			&& m_player->m_UITime > 2.0f)
		{
			//制限時間を減らしていく。
			m_gameTime -= g_gameTime->GetFrameDeltaTime();
		}
		//中間地点に到達しているなら
		if (Try == true)
		{
			//////////////////////////////////////
			////ここから大砲移動後に必要ないオブジェクトを削除する。
			//////////////////////////////////////
			DeleteGO(FindGO<GroundRoad>("groundroad"));
			DeleteGO(FindGO<GroundMove>("groundmove"));
			DeleteGO(FindGO<Stairs>("stairs"));
			DeleteGO(FindGO<Windmill>("windmill"));
			DeleteGO(FindGO<Fort>("fort"));
			const auto& rock_bigs = FindGOs<Rock_Big>("rock_big");
			for (auto rock_big : rock_bigs)
			{
				DeleteGO(rock_big);
			}
			const auto& rings = FindGOs<Ring>("ring");
			for (auto ring : rings)
			{
				DeleteGO(ring);
			}
			const auto& pipes = FindGOs<Pipe>("pipe");
			for (auto pipe : pipes)
			{
				DeleteGO(pipe);
			}
			const auto& shrubs = FindGOs<Shrub>("shrub");
			for (auto shrub : shrubs)
			{
				DeleteGO(shrub);
			}
			//////////////////////////////////////
			////大砲移動後に必要ないオブジェクトを削除するのはここまで。
			//////////////////////////////////////
		}

		//強制終了コマンド*お仕事フェスタ用
		if (g_pad[0]->IsPress(enButtonRB1) && g_pad[0]->IsPress(enButtonLB1) &&
			g_pad[0]->IsPress(enButtonA) && g_pad[0]->IsPress(enButtonB)
			&& g_pad[0]->IsPress(enButtonStart))
		{
			m_fade->StartFadeOut();
			DeleteGO(m_player);
			DeleteModel();
			return;
		}
		//強制リスポーンコマンド*お仕事フェスタ用
		if (g_pad[0]->IsPress(enButtonRB1) && g_pad[0]->IsPress(enButtonLB1) &&
			g_pad[0]->IsPress(enButtonA) && g_pad[0]->IsPress(enButtonB)
			&& g_pad[0]->IsPress(enButtonSelect))
		{
			m_fade->StartFadeOut();
			DeleteGO(FindGO<GameCamera>("gamecamera"));
			DeleteGO(m_player);
			m_player = NewGO<Player>(0, "player");
			m_player->Dead = false;
			m_player->Fall = false;
			m_isWaitFadeout = true;
			return;
		}
	}
	void Game::Retry()
	{
		//プレイヤーがゴールしているなら
		if (m_player->Goal == true)
		{
			//プレイヤーを削除する。
			DeleteGO(m_player);
			//フェードアウトにする。
			m_fade->StartFadeOut();
			//先に一部のモデルを削除する。
			DeleteModel();
			return;
		}
		else
		{
			//制限時間が0秒なら
			if (m_gameTime <= 0)
			{
				//プレイヤーを削除する。
				DeleteGO(m_player);
				//フェードアウトにする。
				m_fade->StartFadeOut();
				//先に一部のモデルを削除する。
				DeleteModel();
				return;
			}
			//体力（残機）を１減らす
			HP--;
			//体力（残機）が残っているなら
			if (HP > ZERO)
			{
				//フェードアウトにする。
				m_fade->StartFadeOut();
				//ゲームカメラを削除する。
				DeleteGO(FindGO<GameCamera>("gamecamera"));
				//プレイヤーのオブジェクトを作成する。
				m_player = NewGO<Player>(0, "player");
				//プレイヤーの死亡状態を処理しない。
				m_player->Dead = false;
				//プレイヤーの落下状態を処理しない。
				m_player->Fall = false;
				////フェードアウト中にする。
				m_isWaitFadeout = true;
			}
			//体力（残機）が残っていないなら
			else
			{
				//フェードアウトにする。
				m_fade->StartFadeOut();
				//先に一部のモデルを削除する。
				DeleteModel();
			}
		}
	}
	void Game::DeleteModel()
	{
		//////////////////////////////////////
		//ここからプレイヤーの位置情報が必要なオブジェクトを削除する。
		//////////////////////////////////////
		DeleteGO(FindGO<GameCamera>("gamecamera"));
		DeleteGO(FindGO<FortTop>("forttop"));
		DeleteGO(FindGO<Fort>("fort"));
		DeleteGO(FindGO<GoalPoint>("goalpoint"));
		const auto& bards = FindGOs<Bard>("bard");
		for (auto bard : bards)
		{
			DeleteGO(bard);
		}
		const auto& pebbles = FindGOs<Pebble>("pebble");
		for (auto pebble : pebbles)
		{
			DeleteGO(pebble);
		}
		const auto& enemy_greens = FindGOs<Enemy_Green>("enemy_green");
		for (auto enemy_green : enemy_greens)
		{
			DeleteGO(enemy_green);
		}
		const auto& enemy_reds = FindGOs<Enemy_Red>("enemy_red");
		for (auto enemy_red : enemy_reds)
		{
			DeleteGO(enemy_red);
		}
		const auto& enemy_yellows = FindGOs<Enemy_Yellow>("enemy_yellow");
		for (auto enemy_yellow : enemy_yellows)
		{
			DeleteGO(enemy_yellow);
		}
		const auto& defaults = FindGOs<Default>("default");
		for (auto defaultd : defaults)
		{
			DeleteGO(defaultd);
		}
		const auto& forwards = FindGOs<Forward>("forward");
		for (auto forward : forwards)
		{
			DeleteGO(forward);
		}
		//////////////////////////////////////
		//プレイヤーの情報が位置必要なオブジェクトを削除するのはここまで。
		//////////////////////////////////////
		//タイトルを作成する。
		NewGO<Title>(0, "title");
		//自身を削除する
		DeleteGO(this);
		//フェードアウト中にする。
		m_isWaitFadeout = true;
	}
}