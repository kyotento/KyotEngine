#include "stdafx.h"
#include "Player.h"

//#define OVERCOOKED_ONE_SPECIFCATION			//overcooked1の仕様にしたい場合定義する。(おそらくバグが発生する)。

//todo　包丁を描画しないように。
namespace {
	const float playerCollidedRadius = 45.f;			//カプセルコライダーの半径。
	const float playerCollidedHeight = 50.f;			//カプセルコライダーの高さ。
}

//コンストラクタ。
Player::Player()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_animationClips[enanimationClip_Idle].Load(L"Assets/animData/chef_idle.tka");				//待機モーション。
	m_animationClips[enanimationClip_Run].Load(L"Assets/animData/chef_run.tka");				//移動。
	m_animationClips[enanimationClip_Cut].Load(L"Assets/animData/chef_cutting.tka");			//物を切る。
	m_animationClips[enanimationClip_Washing].Load(L"Assets/animData/chef_washing.tka");		//皿洗い。
	m_animationClips[enanimationClip_IdleHave].Load(L"Assets/animData/chef_idleHave.tka");		//物を持った状態で待機。
	m_animationClips[enanimationClip_RunHave].Load(L"Assets/animData/chef_runHave.tka");		//物を持った状態で移動。
}

//デストラクタ。
Player::~Player()
{
	//モデルを消す。
	DeleteGO(m_skinModelRender);
	DeleteGO(m_knife);					//包丁を消す。
	if (m_cuttingSound != nullptr) {
		m_cuttingSound->Stop();			//音を消す。
	}
}

#ifdef SPRITE_TEST
SkinModelRender* m_skinModelRender2;
#endif

//クラス生成時に一度だけ呼ばれる処理。
bool Player::Start()
{
	m_startCountDown = FindGO<StartCountdown>("startcountdown");			//ゲーム開始前の更新処理。

	//モデルの初期化諸々。
	m_skinModelRender->Init(L"Assets/modelData/Chef/chef_1.cmo", m_animationClips, enanimationClip_Num, "PSMain", "VSMain", false);
	m_skinModelRender->InitNormalMap(L"Assets/sprite/chef_Normal.dds");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->PlayAnimation(enanimationClip_Idle);

	//キャラコンの座標を指定(m_positionは外部から指定)。
	m_characonPos = m_position;
	//キャラコンの初期化。
	m_characon.Init(playerCollidedRadius, playerCollidedHeight, m_characonPos);

	m_knife = NewGO<Knife>(0, "knife");			//包丁を生成。
	m_knife->SetPosition(m_position);			//座標を更新。

	return true;
}

//毎フレーム更新される処理。
void Player::Update()
{
	//更新処理を開始していない場合処理を終了する。
	if (!m_startCountDown->GetGameStartFlag()) {			//ゲーム更新処理を開始していない場合。
		return;
	}

	//更新処理を開始しているとき。
	Movement(m_controllerNumber);					//プレイヤーの移動処理。
	Rotation();										//プレイヤーの回転処理。
	ForwardDirectionRay(m_controllerNumber);		//プレイヤーの前方方向にrayを飛ばす処理。
	ActionProcessing(m_controllerNumber);			//プレ親―の状態による動作処理。

	if (m_playerState != enanimationClip_Cut) {		//もし切っている状態じゃないとき。
		m_knife->SetPosition(m_position);			//ナイフの座標を指定。
	}
}

//プレイヤーの移動処理。
void Player::Movement(int a)
{
	m_stickPower.x = g_pad[a].GetLStickXF();		//左スティックのX軸の傾き。
	m_stickPower.y = 0.f;							//左スティックのY軸。
	m_stickPower.z = g_pad[a].GetLStickYF();		//左スティックのZ軸の傾き。

	if (m_stickPower.Length() > m_noLongerZero)		//スティックを傾けているとき。
	{
		m_oldPosition = m_position;			//プレイヤーの座標をバックアップ。

		m_move = m_stickPower * m_moveSpeed;				//移動速度の計算。
		m_move.y -= m_fallSpeed;							//落下速度の計算。
		m_position = m_characon.Execute(1.0, m_move);		//キャラコンに移動速度を代入。

		if (m_toHave == false) {		//何も持っていないとき。
			m_playerState = enRun;		//移動状態。
		}
	}

	else {
		if (m_toHave == false) {		//何も持っていないとき。
			m_playerState = enIdle;	//待機状態。
		}
	}

	m_skinModelRender->SetPosition(m_position);			//モデルの座標を更新。
}

//プレイヤーの回転処理。
void Player::Rotation()
{
	//移動していないなら。
	//if (m_position.x == m_oldPosition.x && m_position.z == m_oldPosition.z)
	//{
	//	m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(YisDie.x, YisDie.z));
	//	m_skinModelRender->SetRotation(m_rotation);
	//}

	m_YisDie = m_move;		//移動速度(方向持ち)を代入。
	m_YisDie.y = 0.0f;		//Y軸は必要ないので0を代入。

	//移動しているなら。
	if (m_YisDie.Length() > m_noLongerZero){		
		
		m_YisDie.Normalize();				//正規化して向きを求める。
		m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(m_YisDie.x, m_YisDie.z));			//回転を計算。
		m_skinModelRender->SetRotation(m_rotation);				//モデルの回転を更新する。
	}

	if (m_belongings != nullptr && m_toHave == true) {			//何か持っちるとき。
		m_belongings->SetRotation(m_rotation);					//持っているものの回転を更新する。
	}
}

//プレイヤーのrayがオブジェクトに衝突した時の処理。
void Player::CollideToObject(btCollisionWorld::ClosestRayResultCallback rayRC, int controllerNum)
{
	//オブジェクトの数分ループする。
	for (int i = 0; i <= ObjectAbove::enNumberOfObjectAbove; i++)
	{
		m_userIndexNum = rayRC.m_collisionObject->getUserIndex();	//nに当たっているオブジェクトのIndexを代入。
		if (rayRC.m_collisionObject->getUserIndex() == i) {	//衝突したオブジェクトがi番目だった時。
			rayRC.m_collisionObject->getUserPointer();		//衝突しているもののポインタを返す。
			m_objectAbove = (ObjectAbove*)rayRC.m_collisionObject->getUserPointer();			//m_objectAboveに物が置けるオブジェクトを代入。

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enDesk) {			//机のとき。

				m_desk = (Desk*)rayRC.m_collisionObject->getUserPointer();		//(Desk*)に当たったオブジェクトのポインタを入れる。

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enDelivery) {		//カウンターのとき。

				m_delivery = (Delivery*)rayRC.m_collisionObject->getUserPointer();		//(Delivery*)に当たったオブジェクトのポインタを入れる。

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enDishHold) {		//お皿置きのとき。

				m_dishHold = (DishHold*)rayRC.m_collisionObject->getUserPointer();		//(DishHold*)に当たったオブジェクトのポインタを入れる。

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enDustBox) {		//ゴミ箱のとき。

				m_dustbox = (DustBox*)rayRC.m_collisionObject->getUserPointer();		//(DustBox*)に当たったオブジェクトのポインタを入れる。

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enGasStove) {		//ガスコンロのとき。
					
				m_gasStove = (GasStove*)rayRC.m_collisionObject->getUserPointer();		//(GasStove*)に当たったオブジェクトのポインタを入れる。

			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enKitchen) {		//キッチンのとき。

				m_kitchen = (Kitchen*)rayRC.m_collisionObject->getUserPointer();

				if (g_pad[controllerNum].IsPress(enButtonX))
				{
					if (m_toHave == false) {			//プレイヤーが何も持っていないとき。
						m_playerState = enWashing;			//プレイヤーの状態を洗っている状態に。
						m_objectAbove->TakeThingsDirtyDish(m_cacth);			//乗っている汚れたオブジェクトを検索してm_cactcに。
						m_kitchen->SetDishDirtyInstance((DishDirty*)m_cacth);			//汚れたお皿のインスタンスを設定。
						m_kitchen->DishWashing();			//お皿を洗う関数を呼び出し。
					}
				}
			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enOnionBox) {		//玉ねぎボックスのとき。

				m_onionBox = (OnionBox*)rayRC.m_collisionObject->getUserPointer();

				if (m_toHave == false) {		//何も持っていないとき。
					if (g_pad[controllerNum].IsTrigger(enButtonA) && m_objectAbove->GetState() == ObjectAbove::en_default)
					{
						m_belongings = m_onionBox->NewFood(controllerNum);		//玉ねぎを生成する。生成したものの情報をm_belongingsに代入。

						m_playerState = enIdleHave;			//プレイヤーの状態を物をもって待機している状態に。
					}
				}
			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enTomatoBox) {		//トマトボックスのとき。

				m_tomatoBox = (TomatoBox*)rayRC.m_collisionObject->getUserPointer();

				if (m_toHave == false) {		//何も持っていないとき。
					if (g_pad[controllerNum].IsTrigger(enButtonA) && m_objectAbove->GetState() == ObjectAbove::en_default)
					{
						m_belongings = m_tomatoBox->NewFood(controllerNum);	//トマトを生成する。生成したものの情報をm_belongingsに代入。

						m_playerState = enIdleHave;			//プレイヤーの状態を物をもって待機している状態に。
					}
				}
			}

			if (rayRC.m_collisionObject->getUserIndex() == ObjectAbove::enCuttingDesk) {		//まな板のとき。

				m_cuttingDesk = (CuttingDesk*)rayRC.m_collisionObject->getUserPointer();

				if (m_toHave == false) {		//何も持っていないとき。

					if (g_pad[controllerNum].IsPress(enButtonX) && m_objectAbove->GetState() == ObjectAbove::en_onObject)		//Xを押したとき、何か乗っているとき。
					{
						m_playerState = enCutting;			//プレイヤーの状態を物を切っている状態に。
					}

#ifdef OVERCOOKED_ONE_SPECIFCATION

					//if (m_objectAbove->GetState() == ObjectAbove::en_onObject) {			//何か乗っているとき。
					//	m_objectAbove->TakeThings(m_cacth);			//乗っているものを検索する。
					//	if (g_pad[controllerNum].IsTrigger(enButtonX))		//Xを押したとき。
					//	{
					//		if (m_cacth->GetFoodState() == Belongings::enCutting) {			//乗っている食べ物が切られていた時。
					//			m_cuttingFlag = false;					//材料を切らない状態に変更する。
					//		}
					//		else {				//食べ物が切られていないとき。
					//			if (m_cuttingFlag == false) {			//材料を切っていなかった場合。
					//				m_cuttingFlag = true;				//フラグを返す。
					//			}
					//			else {									//材料を切っているとき。
					//				m_cuttingFlag = false;				//フラグを返す。
					//			}
					//		}
					//	}

					//	if (m_cacth->GetFoodState() == Belongings::enCutting) {			//乗っている食べ物が切られていた時。
					//		m_cuttingFlag = false;					//材料を切らない状態に変更する。
					//	}

					//	if (m_objectAbove->GetState() == ObjectAbove::en_default) {			//何も乗っていない時。
					//		m_cuttingFlag = false;											//材料を切っていない状態に。
					//	}

					//	if (m_cuttingFlag == true) {			//材料を切るフラグがたっているとき。
					//		m_playerState = enCutting;			//プレイヤーの状態を物を切っている状態に。
					//	}
					//}
#endif
				}
			}
		}
	}
}

//プレイヤーの前方方向に線を飛ばす処理。rayとオブジェクトの当たり判定を調べる処理。
void Player::ForwardDirectionRay(int controllerNum)
{
	m_objectAbove = nullptr;		//物を置くとNullになる。

	CVector3 m_movesecond;							//rayの長さ。
	m_move.Normalize();								//正規化し、方向だけを取得する。
	m_movesecond = m_move * m_distance;				//rayの長さを設定。
	btVector3 start(m_position.x, m_position.y + 10, m_position.z);		//rayの始点をbtVector3型に変換。
	m_ray = { m_position.x + m_movesecond.x , m_position.y + m_movesecond.y, m_position.z + m_movesecond.z };		//rayの終点を指定。
	btVector3 end(m_ray.x, m_ray.y + 10, m_ray.z);						//rayの終点をbtVector3型に変換。

	if (m_movesecond.Length() > m_noLongerZero) {						//rayの長さが０以上のとき。
		btCollisionWorld::ClosestRayResultCallback rayRC(start, end);	//rayRCに情報が入っている。
		g_physics.GetDynamicWorld()->rayTest(start, end, rayRC);		//衝突判定。

		if (rayRC.hasHit()){			//衝突しているなら。
			CollideToObject(rayRC,controllerNum);		//プレイヤーの前方方向にオブジェクトがあった時の処理。
		}
	}
}

//プレイヤーの状態による動作処理。
void Player::ActionProcessing(int controllerNum)
{
	switch (m_playerState)		//プレイヤーの状態。
	{
	case enIdle:		//待機状態のとき。

		m_skinModelRender->PlayAnimation(enanimationClip_Idle, m_transitionTime);
		m_animationClips[enanimationClip_Idle].SetLoopFlag(true);

		m_toHave = false;			//何も持っていない。

		PickUpObjects(controllerNum);		//オブジェクトを持つ処理。

		break;

	case enRun:			//移動しているとき。

		m_skinModelRender->PlayAnimation(enanimationClip_Run, m_transitionTime);
		m_animationClips[enanimationClip_Run].SetLoopFlag(true);

		m_toHave = false;			//何も持っていない。

		PickUpObjects(controllerNum);		//オブジェクトを持つ処理。

		break;

	case enCutting:		//物を切っているとき。

		m_skinModelRender->PlayAnimation(enanimationClip_Cut, m_transitionTime);
		m_animationClips[enanimationClip_Cut].SetLoopFlag(true);

		HoldingKnife();				//包丁をプレイヤーに持たせる処理。

		CuttingObject();			//物を切る。

		m_toHave = false;			//何も持っていない。

		break;

	case enWashing:		//皿を洗っているとき。

		m_skinModelRender->PlayAnimation(enanimationClip_Washing, m_transitionTime);
		m_animationClips[enanimationClip_Washing].SetLoopFlag(true);

		m_toHave = false;			//何も持っていない。

		break;

	case enIdleHave:		//物をもって待機している。

		m_skinModelRender->PlayAnimation(enanimationClip_IdleHave, m_transitionTime);
		m_animationClips[enanimationClip_IdleHave].SetLoopFlag(true);

		m_toHave = true;			//何も持っていない。

		if (m_stickPower.Length() > m_noLongerZero){			//移動した時。
			m_playerState = enRunHave;			//状態を変化させる。
		}

		SetFoodPosition();				//食べ物の座標をプレイヤーの前方方向に。
		PutObjects(controllerNum);		//物を置く処理。

		break;

	case enRunHave:		//物を持って走っている。

		m_skinModelRender->PlayAnimation(enanimationClip_RunHave, m_transitionTime);
		m_animationClips[enanimationClip_RunHave].SetLoopFlag(true);

		m_toHave = true;			//何も持っていない。

		if (m_stickPower.Length() > m_noLongerZero == false) {		//移動してなかったとき。
			m_playerState = enIdleHave;			//状態を変化させる。
		}

		SetFoodPosition();				//食べ物の座標をプレイヤーの前方方向に。
		PutObjects(controllerNum);		//物を置く処理。

		break;
	}

	if (m_cuttingSound != nullptr) {					//もしもサウンドが生成されているとき。
		if (m_playerState != enanimationClip_Cut) {		//状態が切っている状態じゃないとき。
			m_cuttingSound->Stop();					//サウンドを消す。
			m_cuttingSound = nullptr;
		}
	}
}

//持っている食べ物の座標を更新する。
void Player::SetFoodPosition()
{
	//todo 低　余裕があれば右手と左手のBoneの座標の中間地点にオブジェクトを置く処理にする。(アニメーションにオブジェクトがついてくるから)。
	m_objPos = m_ray;						//持っているものの座標にプレイヤーのレイ座標を代入。
	m_objPos.y += 60.f;						//気持ち上に座標を上げる。
	m_belongings->SetPosition(m_objPos);	//持っているオブジェクトの座標を設定。

}

//何も乗っていないときに食べ物を置く処理。
void Player::NoRidePutFoods()
{
	if (m_userIndexNum == ObjectAbove::enDesk || m_userIndexNum == ObjectAbove::enOnionBox ||
		m_userIndexNum == ObjectAbove::enTomatoBox || m_userIndexNum == ObjectAbove::enCuttingDesk) {		//食べ物が置けるオブジェクトかどうか。
		m_objectAbove->PutThings(m_belongings);		//設置物の座標にオブジェクトの座標を代入。
		m_objectAbove->SetState(ObjectAbove::en_onObject);					//物を置いたオブジェクトのステートを変更する。
		m_playerState = enIdle;							//プレイヤーのステートを待機状態に。
	}
}

//何も乗っていないときに調理器具を置く処理。
void Player::NoRidePutKichenWares()
{
	if (m_userIndexNum == ObjectAbove::enDesk || m_userIndexNum == ObjectAbove::enGasStove ||
		m_userIndexNum == ObjectAbove::enOnionBox || m_userIndexNum == ObjectAbove::enTomatoBox) {		//調理器具が置けるオブジェクトかどうか。
		m_objectAbove->PutThings(m_belongings);							//設置物の座標にオブジェクトの座標を代入。
		m_objectAbove->SetState(ObjectAbove::en_onObject);				//物を置いたオブジェクトのステートを変更する。
		m_playerState = enIdle;											//プレイヤーのステートを待機状態に。
	}
}

//何も乗っていないときにお皿を置く処理。
void Player::NoRidePutDishs()
{
	if (m_userIndexNum == ObjectAbove::enDesk || m_userIndexNum == ObjectAbove::enOnionBox ||
		m_userIndexNum == ObjectAbove::enTomatoBox) {					//お皿が置けるオブジェクトかどうか。
		m_objectAbove->PutThings(m_belongings);						//設置物の座標にオブジェクトの座標を代入。
		m_objectAbove->SetState(ObjectAbove::en_onObject);			//物を置いたオブジェクトのステートを変更する。
		m_playerState = enIdle;										//プレイヤーの状態を待機状態に。
	}

	if (m_userIndexNum == ObjectAbove::enDelivery) {					//受け渡し口のとき。
		m_objectAbove->PutThings(m_belongings);						//設置物の座標にオブジェクトの座標を代入。
		m_objectAbove->SetDeliveryDishCuisine(m_belongings->GetDishCuisine(m_belongings));			//お皿に載っている料理の情報を受け渡し口に送る。
		DeleteGO(m_belongings);										//お皿を消す。
		m_objectAbove->SetState(ObjectAbove::en_onObject);			//受け渡し口の状態を変更する。
		m_playerState = enIdle;										//プレイヤーの状態を待機状態に。
	}
}

//汚れたお皿を置く処理。
void Player::PutDirtyDishs()
{
	if (m_userIndexNum == ObjectAbove::enKitchen) {					//お皿洗い場のとき。
		m_objectAbove->SetDirtyDishPos(m_belongings);				//設置物の座標にオブジェクトの座標を代入。
		m_objectAbove->SetState(ObjectAbove::en_onObject);			//お皿洗い場の状態を変更する。
		m_playerState = enIdle;										//プレイヤー状態を待機状態に。
	}
}

//物を置く処理。
void Player::PutObjects(int controllerNum)
{
	//todo 仮 持ったものをおけるようになるまでのタイマー。
	m_putTimer -= 0.1f;

	if (g_pad[controllerNum].IsTrigger(enButtonA) && m_putTimer <= 0.f)		//Aボタンを押したときかつ、物を持ってから一定時間が経過した時。
	{
		if (m_objectAbove != nullptr) {					//物を置けるオブジェクトが目の前にあるとき。

			//オブジェクトに何も乗っていないとき。
			if (m_objectAbove->GetState() == ObjectAbove::en_default) {		

				//持っているものが食べ物のとき。
				if (m_belongings->GetIndentValue() == Belongings::enFood) {	

					NoRidePutFoods();
				}

				//持っているものが調理器具の場合。
				if (m_belongings->GetIndentValue() == Belongings::enKitchenWare) {		

					NoRidePutKichenWares();
				}

				//持っているものがお皿の場合。
				if (m_belongings->GetIndentValue() == Belongings::enDish) {

					NoRidePutDishs();
				}
			}

			//持っているものが汚れたお皿のとき。
			if (m_belongings->GetIndentValue() == Belongings::enDirtyDish) {

				PutDirtyDishs();
			}

			//オブジェクトに何か乗っているとき。
			if (m_objectAbove->GetState() == ObjectAbove::en_onObject){

				//持っているものが食べ物のとき。
				if (m_belongings->GetIndentValue() == Belongings::enFood) {			
					if (m_belongings->GetFoodState() == Belongings::enCutting) {			//持っているオブジェクトが切られているとき。
						m_objectAbove->TakeThings(m_cacth);			//乗っているオブジェクトを検索する。
						if (m_cacth->GetIndentValue() == Belongings::enKitchenWare) {			//乗っているものが調理器具だった場合。
							//お鍋に何も入ってないとき。
							if ( m_cacth->GetPotState() == Belongings::enZero) {			
								m_cacth->SetPotFoodType(m_cacth, m_belongings->GetFoodTypeState());			//お鍋に入れる食べ物を設定する。
								m_cacth->SetFoodTypeState(m_belongings->GetFoodTypeState());		//鍋に入れるスープを指定する。
								m_cacth->SetSoupBase(m_cacth);				//鍋にスープを入れる(それっぽいオブジェクトの生成)処理。
								DeleteGO(m_belongings);						//持っているものを消す。
								m_playerState = enIdle;						//状態を待機状態に変更。
							}

							else {			//お鍋に何か入っているとき。
								if (m_cacth->GetPotFoosType(m_cacth) == m_belongings->GetFoodTypeState()) {			//お鍋の中身と持っている食べ物の種類が同じとき。
									if (m_cacth->GetPotState() == Belongings::enOne || m_cacth->GetPotState() == Belongings::enTwo) {		//お鍋にまだ食べ物が入る状態のとき。
										m_cacth->SetSoupBase(m_cacth);				//鍋にスープを入れる(それっぽいオブジェクトの生成)処理。
										DeleteGO(m_belongings);						//持っているものを消す。
										m_playerState = enIdle;						//状態を待機状態に変更。
									}
								}
							}
						}
					}
				}

				//持っているものがお皿のとき。
				if (m_belongings->GetIndentValue() == Belongings::enDish) {			
					m_objectAbove->TakeThings(m_cacth);				//乗っているオブジェクトを検索する。
					if (m_cacth->GetIndentValue() == Belongings::enKitchenWare) {			//乗っているものが調理器具だった場合。
						if (m_cacth->GetPotState() == Belongings::enComplete) {				//乗っているものの状態が完成状態だった時。
							m_cacth->DeleteSoup(m_cacth);			//鍋の中のスープを消す。
							m_belongings->PutDishs(m_belongings, m_cacth->GetFoodTypeState());	//お皿にスープを置く。
							m_belongings->SetDishCuisine(m_belongings, m_cacth->GetGetPotDishCuisine(m_cacth));		//鍋に入っている料理の情報をお皿に送る。
						}
					}
				}
			}
		}
	// ここのコメントを外すとどこにでも食べ物を置くことができる。
	//	else(m_state = enIdle);							//前方方向にオブジェクトがないとき。

		m_putTimer = 0.5f;		//タイマーを初期化。
	}
}

//オブジェクトを拾う処理。
void Player::PickUpObjects(int controllerNum)
{
	if (g_pad[controllerNum].IsTrigger(enButtonA))						//Aボタンを押したとき。
	{
		if(m_toHave == false){			//何も持っていないとき
			if (m_objectAbove != nullptr) {						//目の前にオブジェクトがあるとき。

				//料理提供場のとき処理を終了する。
				if (m_userIndexNum == ObjectAbove::enDelivery) {
					return;
				}

				//お皿洗い場以外のとき。
				if (m_userIndexNum != ObjectAbove::enKitchen) {
					if (m_objectAbove->GetState() == ObjectAbove::en_onObject) {			//オブジェクトに何か乗っているとき。
						m_objectAbove->TakeThings(m_belongings);	//乗っているオブジェクトを検索。
						m_objectAbove->SetState(ObjectAbove::en_default);					//物をとったオブジェクトのステートを変更する。
						m_objectAbove->SetBelongings(nullptr);		//乗っているものをnullに。
						m_toHave = true;							//物を持つフラグ。
						m_playerState = enIdleHave;					//ステート変更。
					}
				}

				//お皿洗い場のとき。
				if (m_userIndexNum == ObjectAbove::enKitchen) {
					m_objectAbove->TakeThings(m_belongings);

					if (m_belongings != nullptr) {				//持つことのできるオブジェクトがあるとき。(汚れたお皿以外)。

						//乗っているものがお皿のとき。
						if (m_belongings->GetIndentValue() == Belongings::enDish) {
							m_objectAbove->TakeThings(m_belongings);		//乗っているオブジェクトを検索。
							m_cacth = m_belongings;							//一度m_cacthに避難。
							m_belongings->PutDishFromKitchen(m_cacth, (Kitchen*)m_objectAbove);		//お皿を一つとる。
							m_belongings = NewGO<Dish>(0, "dish");			//新しくお皿を生成する。
							m_belongings->SetPosition(m_ray);
							m_toHave = true;								//物を持つフラグ。
							m_playerState = enIdleHave;						//ステート変更。
						}
					}
				}
			}
		}
	}
}

//物を切る処理。
void Player::CuttingObject()
{
	m_objectAbove->TakeThings(m_belongings);		//置いてあるオブジェクトを検索。

	if (m_cuttingSound == nullptr) {			//サウンドが生成されていないとき。
		//食べ物を切る音。
		m_cuttingSound = NewGO<Sound>(0, "sound");									//サウンド。
		m_cuttingSound->Init(L"Assets/sound/soundEffect/cuttings.wav", true);		//初期化。
		m_cuttingSound->Play();														//更新処理。
	}

	m_belongings->GaugeGeneration(true, 1.f, 5.f);				//ゲージを生成する。
}

//包丁をプレイヤーに持たせる処理。
void Player::HoldingKnife()
{
	int boneNum;			//骨の配列の番号を保持するためのもの。
	m_skelton = &m_skinModelRender->GetSkinModel().GetSkeleton();		//ほねのインスタンスを取得。
	boneNum = m_skelton->FindBoneID(L"Bone008");		//包丁を持つBoneの名前。
	Bone* m_bone;			//骨っこジャーキー。

	//座標を引き抜く。
	CVector3 Bonepos;		//骨の座標。

	m_bone = m_skelton->GetBone(boneNum);			//骨の情報を渡す。

	CMatrix boneRot;						//ボーンの行列を保持するやつ。
	boneRot = m_bone->GetMatrix();			//ボーンの行列を代入。
	Bonepos.x = boneRot.m[3][0];			//X軸。
	Bonepos.y = boneRot.m[3][1];			//Y軸。
	Bonepos.z = boneRot.m[3][2];			//Z軸。

	CQuaternion Bonerote;					//骨の回転を引き抜くよ。
	Bonerote.SetRotation(boneRot);			//ボーンの行列から回転行列を抽出。

	m_knife->SetPosition(Bonepos);			//包丁に骨の座標を代入。
	m_knife->SetRotation(Bonerote);			//包丁に骨の回転を代入。
}