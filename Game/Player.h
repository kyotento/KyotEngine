#pragma once
#include "character/CharacterController.h"
#include "Desk.h"
#include "DishHold.h"
#include "GasStove.h"
#include "DustBox.h"
#include "CuttingDesk.h"
#include "Kitchen.h"
#include "Delivery.h"
#include "TomatoBox.h"
#include "OnionBox.h"
#include "Knife.h"
#include "Belongings.h"
#include "Tomato.h"
#include "ObjectAbove.h"
#include "Gauge.h"
#include "math/Vector.h"
#include "SoupBase.h"
/// <summary>
/// プレイヤーの基底クラス。
/// </summary>
class Desk;
class DishHold;
class GasStove;
class DustBox;
class CuttingDesk;
class Kitchen;
class Delivery;
class TomatoBox;
class OnionBox;
class Knife;
class Belongings;
class Tomato;
class Player : public GameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

	/// <summary>
	/// プレイヤー移動クラス。
	/// </summary>
	/// <param name="a">コントローラー番号</param>
	void Movement(int a);

	/// <summary>
	/// プレイヤー回転クラス。
	/// </summary>
	void Rotation();

	/// <summary>
	/// プレイヤーの動作処理。
	/// </summary>
	/// <param name="controllerNum">コントローラー番号</param>
	void ActionProcessing(int controllerNum);

	/// <summary>
	/// プレイヤーの前方方向に線を飛ばす処理。
	/// rayとオブジェクトの当たり判定を調べる処理。
	/// </summary>
	/// <param name="controllerNum">コントローラー番号</param>
	/// <remarks>
	/// 前方方向にオブジェクトがあるかを調べるためのもの。
	/// </remarks>
	void ForwardDirectionRay(int controllerNum);

	/// <summary>
	/// 包丁をもたせる。
	/// </summary>
	void HoldingKnife();

	/// <summary>
	/// もっている食べ物の座標を設定する。
	/// </summary>
	void SetFoodPosition();

	/// <summary>
	/// 食べ物を置く処理。
	/// </summary>
	/// <param name="controllerNum">コントローラー番号</param>
	void PutObjects(int controllerNum);

	/// <summary>
	/// 何も乗っていないときに食べ物を置く処理。
	/// </summary>
	void NoRidePutFoods();

	/// <summary>
	/// 何も乗っていないときに調理器具を置く処理。
	/// </summary>
	void NoRidePutKichenWares();

	/// <summary>
	/// 何も乗っていないときにお皿を置く処理。
	/// </summary>
	void NoRidePutDishs();

	/// <summary>
	///	何も乗っていないときに汚れたお皿を置く処理。
	/// </summary>
	void NoRidePutDirtyDishs();

	/// <summary>
	/// オブジェクトを拾う。
	/// </summary>
	/// <param name="controllerNum">コントローラー番号</param>
	void PickUpObjects(int controllerNum);

	/// <summary>
	/// オブジェクトを切る処理。
	/// </summary>
	void CuttingObject();

	/// <summary>
	/// アニメーション。
	/// </summary>
	enum EnAnimationClip
	{
		enanimationClip_Idle,			//待機。
		enanimationClip_Run,			//何も持たずに移動。
		enanimationClip_Cut,			//物を切る。
		enanimationClip_Washing,		//皿を洗う。
		enanimationClip_IdleHave,		//物をもって待機。
		enanimationClip_RunHave,		//物をもって移動。
		enanimationClip_Num,			//アニメーションの数。
	};

	/// <summary>
	/// プレイヤーの状態。
	/// </summary>
	enum enPlayerState
	{
		enIdle,							//待機状態。
		enRun,							//移動。
		enCutting,						//物を切る。
		enWashing,						//皿を洗う。
		enIdleHave,						//物をもって待機している。
		enRunHave,						//物をもって移動している。
	};

	AnimationClip m_animationClips[enanimationClip_Num];		//アニメーションの数。

	/// <summary>
	/// プレイヤーの座標を取得する。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// 持つことのできるものを代入する。
	/// </summary>
	/// <param name="belon">持ち物</param>
	void SetBelongings(Belongings* belon)
	{
		m_belongings = belon;
	}

	/// <summary>
	///	ナイフのインスタンスを取得。
	/// </summary>
	/// <returns>ナイフ</returns>
	Knife *GetKnife()
	{
		return m_knife;
	}

	/// <summary>
	/// プレイヤーのrayがオブジェクトに衝突した時の処理。
	/// </summary>
	/// <param name="rayRC"></param>
	/// <param name="controllerNum">コントローラー番号</param>
	void CollideToObject(btCollisionWorld::ClosestRayResultCallback rayRC, int controllerNum);

protected:

	int userIndexNum = 0;									//当たっているインデックスを代入。
	int m_controllerNumber = 0;								//todo 仮　プレイヤー１のコントローラー番号。

	bool m_toHave = false;									//何かを持っているかどうか。
	bool m_knifeflag = false;								//ナイフがNewされたかどうか。

	float m_transitionTime = 0.1f;							//アニメーションが切り替わるときの遷移時間。
	float m_moveSpeed = 7.5f;								//移動速度。
	float m_fallSpeed = 9.8f;								//落下速度。
	float m_distance = 70.0f;								//Rayの飛ばせる距離。
	float m_noLongerZero = 0.00001f;						//限りなく０に近い値。
	float m_putTimer = 0.5f;								//持ったオブジェクトを置けるようになるまでの時間。

	CVector3 m_objPos = CVector3::Zero();					//持ったものノ座標。
	CVector3 m_position = CVector3::Zero();					//プレイヤーの座標。
	CVector3 m_characonPos = CVector3::Zero();				//キャラコンの座標。
	CVector3 m_scale = CVector3::One();						//拡大率。
	CVector3 m_move = CVector3::Zero();						//キャラコンとかプレイヤーの移動速度を計算したもの。(方向持ち)。
	CVector3 m_oldPosition = CVector3::Zero();				//キャラクターの１フレーム前の座標。
	CVector3 m_stickPower = CVector3::Zero();				//左スティックの傾き具合を保持するためのもの。
	CVector3 m_YisDie = CVector3::Zero();					//XZ座標のみを保持。プレイヤーの向きの計算に使う。
	CVector3 m_ray = CVector3::Zero();						//レイの終点。

	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	CharacterController m_characon;							//キャラコン。

	SkinModelRender* m_skinModelRender = nullptr;			//スキンモデル。

	enPlayerState m_playerState = enIdle;					//プレイヤーの状態。

	Desk* m_desk = nullptr;						//机。
	DishHold* m_dishHold = nullptr;				//お皿置き。
	GasStove* m_gasStove = nullptr;				//ガスコンロ。
	DustBox* m_dustbox = nullptr;				//ゴミ箱。
	CuttingDesk* m_cuttingDesk = nullptr;		//まな板。
	Kitchen* m_kitchen = nullptr;				//水洗い場。
	Delivery* m_delivery = nullptr;				//受け渡し所。
	TomatoBox* m_tomatoBox = nullptr;			//トマトの箱。
	OnionBox* m_onionBox = nullptr;				//玉ねぎの箱。
	Knife* m_knife = nullptr;					//ナイフ。
	Skeleton* m_skelton = nullptr;				//サンズ(スケルトン)。
	Belongings* m_belongings = nullptr;			//持つことができるもの。
	Belongings* m_cacth = nullptr;				//物を置くことのできるオブジェクトに乗ってある、持つことのできるオブジェクトを検索したものを格納するためのもの。
	Belongings* m_putSoup = nullptr;
	Tomato* m_tomato = nullptr;					//トマト。
	ObjectAbove* m_objectAbove = nullptr;		//物を置くことができるオブジェクト。
	Gauge* m_gauge = nullptr;					//ゲージ。
	SoupBase* m_soupBase = nullptr;				//スープ。


private:

};

