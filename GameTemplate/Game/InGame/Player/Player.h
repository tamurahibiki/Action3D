#pragma once
using namespace std;

/// <summary>
/// プレイヤークラス
/// </summary>
namespace App {
	class EffectList;
	class SoundList;
	class Game;
	class FortTop;
	class Fort;
	class GoalPoint;
	class GameCamera;

	class Player :public IGameObject
	{
		//プレイヤーのステート
		enum EnPlayerState {
			enPlayerState_Idle,       //待機
			enPlayerState_Idle2,      //放置中待機
			enPlayerState_Walk,       //歩き
			enPlayerState_Dash,       //ダッシュ
			enPlayerState_Dash_Max,   //スーパーダッシュ(最速ダッシュ)
			enPlayerState_Jump,       //ジャンプ
			enPlayerState_Drop,       //ヒップドロップ
			enPlayerState_Fort_Ground,//大砲移動(地上）
			enPlayerState_Fort_Air,   //大砲移動(空中）
			enPlayerState_Goal,       //ゴール(後転）
			enPlayerState_Goal2,      //ゴール(ダンス）
			enPlayerState_Dead,       //死亡
			enPlayerState_Fall        //落下
		};
	public:
		Player();
		~Player();
		bool Start();
		void Update();
		void Render(RenderContext& rc);
		//移動処理
		void Move();
		//スティック処理
		void Move_Stick();
		//地上移動処理
		void Move_Ground();
		//空中移動処理
		void Move_Air();
		//大砲移動処理
		void Move_Fort();
		//ゴール移動処理
		void Move_Goal();
		//移動ステート処理
		void Move_Common();
		//HP処理
		void HP();
		//制限時間処理
		void TimeLimit();
		//回転処理
		void Rotation();
		//当たり判定
		void Collision();
		//ステート処理
		void ManageState();
		//アニメーション処理
		void PlayAnimation();
		//雨のエフェクト
		void RainEffect();

		/// <summary>
		/// 移動方向の計算に、1フレーム前の移動方向を使う機能を有効にする。
		/// </summary>
		void EnableUsingLastFrameMoveDirection()
		{
			m_usingLastFrameMoveDirection = true;
		}
		/// <summary>
		/// 移動方向の計算に、1フレーム前の移動方向を使う機能を無効にする。
		/// </summary>
		void DisableUsingLastFrameMoveDirection()
		{
			m_usingLastFrameMoveDirection = false;
		}
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
		/// <summary>
		/// 踏み台ジャンプが可能。
		/// </summary>
		/// <returns>可能ならtrue。</returns>
		bool JunpCount = false;
		/// <summary>
		/// 大砲に乗り込む。
		/// </summary>
		/// <returns>大砲に乗り込むならtrue。</returns>
		bool Fort_Idle = false;
		/// <summary>
		/// 大砲移動で上昇する。
		/// </summary>
		/// <returns>大砲移動で上昇するならtrue。</returns>
		bool Fort_Move = false;
		/// <summary>
		/// 大砲移動で下降する。
		/// </summary>
		/// <returns>大砲移動で下降するならtrue。</returns>
		bool Fort_Top = false;
		/// <summary>
		/// プレイヤーを描画しない。
		/// </summary>
		/// <returns>プレイヤーを描画しないならtrue。</returns>
		bool PlayerNotDraw = false;
		/// <summary>
		/// ゴール状態である。
		/// </summary>
		/// <returns>ゴール状態であるならtrue。</returns>
		bool Goal = false;
		/// <summary>
		/// 死亡状態である。
		/// </summary>
		/// <returns>死亡状態であるならtrue。</returns>
		bool Dead = false;
		/// <summary>
		/// 落下状態である。
		/// </summary>
		/// <returns>落下状態であるならtrue。</returns>
		bool Fall = false;
		/// <summary>
		/// 通常カメラ状態である。
		/// </summary>
		/// <returns>通常カメラ状態であるならtrue。</returns>
		bool Default = true;
		/// <summary>
		/// 奥行きカメラ状態である。
		/// </summary>
		/// <returns>奥行きカメラ状態であるならtrue。</returns>
		bool Forward = false;
		/// <summary>
		/// ジャンプ中である。
		/// </summary>
		/// <returns>ジャンプ状態であるならtrue。</returns>
		bool PlayerJunp = false;
		/// <summary>
		/// ブロックが頭に衝突している。
		/// </summary>
		/// <returns>ブロックが頭に衝突しているtrue。</returns>
		bool Block_Hed = false;
		/// <summary>
		/// 敵を連続で踏みつけると1ずつ加算する。
		/// </summary>
		/// <returns>連続で敵を踏みつけた数。一度着地すると0にする。</returns>
		int Enemy_JunpCount = 0;
		/// <summary>
		/// UI表示開始時間。
		/// </summary>
		float m_UITime = 0.0f;
		/// <summary>
		/// 制限時間。(int型に直す)
		/// </summary>
		int Game_Timer = 0;
		/// <summary>
		/// クリアを通知する。
		/// </summary>
		/// <returns>クリアを通知するならtrue。</returns>
		bool Clear = false;

	private:
		//歩きエフェクト。
		void WalkEffect();
		//ダッシュエフェクト。
		void DashEffect();
		//スーパーダッシュ準備完了のエフェクト。
		void Dash_MaxEffect();
		//スーパーダッシュの火花のエフェクト。
		void Dash_Max_FirstEffect();
		//スーパーダッシュの火花の焦げ跡のエフェクト。
		void Dash_Max_First2Effect();
		//ジャンプ中のエフェクト。
		void JumpEffect();
		//ヒップドロップ着地のエフェクト。
		void Drop_EndEffect();
		//ゲームクリアのエフェクト。
		void ClearEffect();
		//頭の攻撃判定。
		void HedCollision();
		//足の攻撃判定。
		void LegCollision();
		//お尻の攻撃判定。
		void HipCollision();
		//共通ステートの遷移処理。
		void ProcessCommonStateTransition();
		//ジャンプステートの遷移処理。
		void ProcessJumpStateTransition();
		//ヒップドロップステートの遷移処理。
		void ProcessDropStateTransition();
		//大砲移動ステートの遷移処理。
		void ProcessFortStateTransition();
		//ゴール(後転）ステートの遷移処理。
		void ProcessGoalStateTransition();
		//ゴール(ダンス）ステートの遷移処理。
		void ProcessGoal2StateTransition();
		//死亡ステートの遷移処理。
		void ProcessDeadStateTransition();
		//アニメーションの読み込み。
		void InitAnimation();
		//画像の読み込み。
		void InitSprite();
		//アニメーションイベント用の関数。
		void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

		//プレイヤーのアニメーションクリップ。
		enum EnAnimationClip {
			enAnimationClip_Idle,       //待機
			enAnimationClip_Idle2,      //放置中待機
			enAnimationClip_Walk,       //歩き
			enAnimationClip_Dash,       //ダッシュ
			enAnimationClip_Dash_Max,   //スーパーダッシュ(最速ダッシュ)
			enAnimationClip_Jump,       //ジャンプ
			enAnimationClip_Drop,       //ヒップドロップ
			enAnimationClip_Fort_Ground,//大砲移動(地上）
			enAnimationClip_Fort_Air,   //大砲移動(空中）
			enAnimationClip_Goal,       //ゴール(後転）
			enAnimationClip_Goal2,      //ゴール(ダンス)
			enAnimationClip_Dead,       //死亡
			enAnimationClip_Fall,       //落下
			enAnimationCilp_Num,
		};

		ModelRender         m_modelRender;                     //モデルレンダー
		Vector3             m_position;                        //座標
		Quaternion          m_rotation;                        //回転
		Vector3             m_forward = Vector3::AxisZ;        //正面ベクトル
		Vector3             m_scale;                           //大きさ
		Vector3             m_moveSpeed;                       //移動速度
		Vector3             m_inertiaSpeed;                    //慣性
		Vector3				m_lastFrameLStick;				   //1フレーム前のLスティックの入力量
		Vector3				m_lastFrameMoveDirection;		   //1フレーム前の移動方向
		bool				m_usingLastFrameMoveDirection;	   //1フレーム前の移動方向を使う？
		EnPlayerState		m_playerState = enPlayerState_Idle;//プレイヤーのステート

		EffectList* m_effectlist = nullptr;              //エフェクトリスト
		SoundList* m_soundlist = nullptr;             //サウンドリスト
		CollisionObject* m_collisionObject;                 //コリジョンオブジェクト
		CharacterController m_charaCon;                        //キャラクターコントローラー
		EffectEmitter* m_effectEmitter = nullptr;         //エフェクト
		AnimationClip       m_animClips[enAnimationCilp_Num];  //アニメーションクリップ
		Game* m_game = nullptr;                  //ゲーム
		Fort* m_fort = nullptr;                  //大砲
		FortTop* m_fortTop = nullptr;               //大砲移動の頂点ポイント
		GoalPoint* m_goal = nullptr;                  //ゴールポイント
		GameCamera* m_gameCamera = nullptr;            //ゲームカメラ

		SpriteRender		m_aiconSprite;  //キャラクターアイコン画像
		SpriteRender        m_timerSprite;
		SpriteRender		m_clear;        //クリア画像
		wstring				m_hpCountwst;   //HP文字列
		wstring				m_timeLimittwst;//制限時間文字列
		FontRender          m_hpCountFont;  //HPフォント
		FontRender          m_timeLimitFont;//制限時間フォント

		float               m_startTime = 0.0f;      //操作開始時間
		float			    m_idleTime = 0.0f;       //待機時間。
		float               m_jumpTime = 0.0f;       //ジャンプのクールタイム
		float               m_jumpInputTime = 0.0f;  //ジャンプボタンの入力時間
		float               m_moveTime = 0.0f;       //MoveEffectの再生開始時間         
		float               m_dashTime = 0.0f;       //ダッシュした時間
		float               m_dropTime = 1.0f;       //ヒップドロップの着地硬直時間
		float               m_fortTime = 0.0f;       //大砲移動(地上)出来る時間

		/// <summary>
		/// スーパーダッシュ準備完了のエフェクトを再生する。
		/// </summary>
		/// <returns>エフェクトを再生するならtrue。</returns>
		bool Dash_Max_Effect = true;
		/// <summary>
		/// スーパーダッシュの火花、焦げ跡のエフェクトを再生する。
		/// </summary>
		/// <returns>エフェクトを再生するならtrue。</returns>
		bool Dash_Max_Start_Effect = true;
		/// <summary>
		/// 着地のエフェクトを再生する。
		/// </summary>
		/// <returns>エフェクトを再生するならtrue。</returns>
		bool Jump_End_Effect = false;
		/// <summary>
		/// 重力は通常の状態か。
		/// </summary>
		/// <returns>通常の状態ならtrue。</returns>
		bool Gravity = true;
		/// <summary>
		/// ジャンプは可能な状態か。
		/// </summary>
		/// <returns>可能な状態ならtrue。</returns>
		bool SecondJump = true;
		/// <summary>
		/// ヒップドロップ中か。
		/// </summary>
		/// <returns>ヒップドロップ中ならtrue。</returns>
		bool Drop = false;
		/// <summary>
		/// ヒップドロップ準備中か。
		/// </summary>
		/// <returns>ヒップドロップ準備中ならtrue。</returns>
		bool Stop = false;
		/// <summary>
		/// 大砲移動効果音を再生する。
		/// </summary>
		/// <returns>大砲移動効果音を再生出来るならtrue。</returns>
		bool Fort_Move_Se = true;
		/// <summary>
		/// ゴール(ダンス)が出来るか。
		/// </summary>
		/// <returns>ゴール(ダンス)が出来るならtrue。</returns>
		bool Goal2 = false;
		/// <summary>
		/// スティックの操作がされているか。
		/// </summary>
		/// <returns>スティックの操作がされているならtrue。</returns>
		bool Stick = false;
		/// <summary>
		/// エネミーを連続で踏みつけた時の効果音を再生する。
		/// </summary>
		/// <returns>エネミーを連続で踏みつけた時の効果音を再生するならtrue。</returns>
		bool Enemy_JumpCountSE = true;
		/// <summary>
		/// 落下の効果音を再生する。
		/// </summary>
		/// <returns>落下の効果音を再生するならtrue。</returns>
		bool Fall_SE = true;
		/// <summary>
		/// プレイヤーが回転する地面に乗っているか。
		/// </summary>
		/// <returns>プレイヤーが回転する地面に乗っているならtrue。</returns>
		bool OnGroundMove = false;
		/// <summary>
		/// プレイヤーがブロックに乗っているか。
		/// </summary>
		/// <returns>プレイヤーがブロックに乗っているならtrue。</returns>
		bool OnBlock = false;
		/// <summary>
		/// プレイヤーがブロックに横から衝突しているか。
		/// </summary>
		/// <returns>プレイヤーがブロックに横から衝突ならtrue。</returns>
		bool HitBlock = false;
		/// <summary>
		/// 復活処理が可能か。
		/// </summary>
		/// <returns>復活処理が可能ならtrue。</returns>
		bool ReTry = true;
	};
}