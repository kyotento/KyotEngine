#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_animationClips[enanimationClip_Idle].Load(L"Assets/animData/chef_idle.tka");				//待機モーション。
	m_animationClips[enanimationClip_Run].Load(L"Assets/animData/chef_run.tka");				//移動。
	m_animationClips[enanimationClip_Cut].Load(L"Assets/animData/chef_cutting.tka");			//物を切る。
	m_animationClips[enanimationClip_Washing].Load(L"Assets/animData/chef_washing.tka");		//皿洗い。
	m_animationClips[enanimationClip_IdleHave].Load(L"Assets/animData/chef_idleHave.tka");		//物を持った状態で待機。
	m_animationClips[enanimationClip_RunHave].Load(L"Assets/animData/chef_runHave.tka");		//物を持った状態で移動。

	//キャラコンの初期化。
	m_characon.Init(45.f, 50.f, m_characonPos);
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

bool Player::Start()
{


	return true;
}

void Player::Update()
{

}

void Player::Movement(int a)
{
	
	stickPower.x = g_pad[a].GetLStickXF();
	stickPower.y = 0.f;
	stickPower.z = g_pad[a].GetLStickYF();

	if (stickPower.Length() > m_noLongerZero)
	{
		m_oldPosition = m_position;

		m_move = stickPower * m_moveSpeed;
		m_move.y -= m_fallSpeed;
		m_position = m_characon.Execute(1.0, m_move);

		if (m_toHave == false) {
			m_state = enRun;	//移動状態。
		}
	}

	else {
		if (m_toHave == false) {
			m_state = enIdle;	//待機状態。
		}
	}


		
	m_skinModelRender->SetPosition(m_position);

}

void Player::Rotation()
{
	//移動していないなら。
	//if (m_position.x == m_oldPosition.x && m_position.z == m_oldPosition.z)
	//{
	//	m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(YisDie.x, YisDie.z));
	//	m_skinModelRender->SetRotation(m_rotation);
	//}


	YisDie = m_move;
	YisDie.y = 0.0f;

	//移動しているなら。
	if (YisDie.Length() > m_noLongerZero){
		
		YisDie.Normalize();
		m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(YisDie.x, YisDie.z));
		m_skinModelRender->SetRotation(m_rotation);

	}

}

void Player::ForwardDirectionRay(int a)
{
	m_objectAbove = nullptr;		//物を置くとNullになる。

	CVector3 m_movesecond;							//rayの長さ。
	m_movesecond = m_move * m_distance;				//rayの長さを設定。
	btVector3 start(m_position.x, m_position.y + 10, m_position.z);		//btVector3型に変換。
	m_ray = { m_position.x + m_movesecond.x , m_position.y + m_movesecond.y, m_position.z + m_movesecond.z };		//rayの終点を指定。
	btVector3 end(m_ray.x, m_ray.y + 10, m_ray.z);						//btVector3型に変換。

	if (m_movesecond.Length() > m_noLongerZero) {			//rayの長さが０以上のとき。
		btCollisionWorld::ClosestRayResultCallback rayRC(start, end);	//rayRCに情報が入っている。
		g_physics.GetDynamicWorld()->rayTest(start, end, rayRC);			//衝突判定。

		if (rayRC.hasHit())			//衝突しているなら。
		{
			////Desk。
			//if (rayRC.m_collisionObject->getUserIndex() == 1) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			//
			////Delivery。
			//if (rayRC.m_collisionObject->getUserIndex() == 2) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////DishHold。
			//if (rayRC.m_collisionObject->getUserIndex() == 3) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////DustBox。
			//if (rayRC.m_collisionObject->getUserIndex() == 4) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////GasStove。
			//if (rayRC.m_collisionObject->getUserIndex() == 5) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////Kitchen。
			//if (rayRC.m_collisionObject->getUserIndex() == 6){
			//	rayRC.m_collisionObject->getUserPointer(); 
			//}
			////OnionBox。
			//if (rayRC.m_collisionObject->getUserIndex() == 7) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}
			////TomatoBox。
			//if (rayRC.m_collisionObject->getUserIndex() == 8) {
			//	rayRC.m_collisionObject->getUserPointer();
			//}

			for (int i = 1; i <= m_objectNum; i++)
			{
				int n = rayRC.m_collisionObject->getUserIndex();	//nに当たっているオブジェクトのIndexを代入。
				if (rayRC.m_collisionObject->getUserIndex() == i) {	//衝突したオブジェクトがi番目だった時。
					rayRC.m_collisionObject->getUserPointer();		//衝突しているもののポインタを返す。
					m_objNum = i;									//オブジェクトナンバー格納庫にiを代入。
					m_objectAbove = (ObjectAbove*)rayRC.m_collisionObject->getUserPointer();

					if (i == 1) {		//机のとき。

						m_desk = (Desk*)rayRC.m_collisionObject->getUserPointer();	//(Desk*)に当たったオブジェクトのポインタを入れる。

					}

					if (i == 2) {		//カウンターのとき。

						m_delivery = (Delivery*)rayRC.m_collisionObject->getUserPointer();	

					}

					if (i == 3) {		//お皿置きのとき。

						m_dishHold = (DishHold*)rayRC.m_collisionObject->getUserPointer();

					}

					if (i == 4) {		//ゴミ箱のとき。

						m_dustbox = (DustBox*)rayRC.m_collisionObject->getUserPointer();

					}

					if (i == 5) {		//ガスコンロのとき。

						m_gasStove = (GasStove*)rayRC.m_collisionObject->getUserPointer();	//(GasStove*)に当たったオブジェクトのポインタを入れる。

					}

					if (i == 6) {		//キッチンのとき。

						m_kitchen = (Kitchen*)rayRC.m_collisionObject->getUserPointer();

						//todo 絶　仮 実際は汚れたお皿があるとき。
						if (g_pad[0].IsPress(enButtonB))
						{
							m_state = enWashing;
						}
					}

					if (i == 7) {		//玉ねぎボックスのとき。

						m_onionBox = (OnionBox*)rayRC.m_collisionObject->getUserPointer();

						if (m_toHave == false) {
							if (g_pad[a].IsTrigger(enButtonA) && m_objectAbove->GetState() == 0)
							{
								m_belongings = m_onionBox->NewFood(a);		//玉ねぎを生成する。生成したものの情報をm_belongingsに代入。

								m_state = enIdleHave;
							}
						}
					}

					if (i == 8) {		//トマトボックスのとき。

						m_tomatoBox = (TomatoBox*)rayRC.m_collisionObject->getUserPointer();

						if (m_toHave == false) {		//何も持っていないとき。
							if (g_pad[a].IsTrigger(enButtonA) && m_objectAbove->GetState() == 0)
							{
								m_belongings = m_tomatoBox->NewFood(a);	//トマトを生成する。生成したものの情報をm_belongingsに代入。

								m_state = enIdleHave;
							}
						}
					}

					if (i == 9) {		//まな板のとき。

						m_cuttingDesk = (CuttingDesk*)rayRC.m_collisionObject->getUserPointer();

						if (m_toHave == false) {		//何も持っていないとき。
							if (g_pad[a].IsPress(enButtonX) && m_objectAbove->GetState() == 1)		//Xを押したとき、何か乗っているとき。
							{
								m_state = enCutting;
							}
						}
					}
				}
			}
		}
	}
}

void Player::ActionProcessing(int a)
{

	switch (m_state)
	{
	case enIdle:		//待機状態のとき。

		m_skinModelRender->PlayAnimation(enanimationClip_Idle, m_transitionTime);
		m_animationClips[enanimationClip_Idle].SetLoopFlag(true);

		m_toHave = false;

		PickUpObjects(a);		//オブジェクトを持つ処理。

		break;

	case enRun:			//移動しているとき。

		m_skinModelRender->PlayAnimation(enanimationClip_Run, m_transitionTime);
		m_animationClips[enanimationClip_Run].SetLoopFlag(true);

		m_toHave = false;

		PickUpObjects(a);		//オブジェクトを持つ処理。

		break;

	case enCutting:		//物を切っているとき。

		m_skinModelRender->PlayAnimation(enanimationClip_Cut, m_transitionTime);
		m_animationClips[enanimationClip_Cut].SetLoopFlag(true);

		HoldingKnife();

		CuttingObject();		//物を切る。

		m_toHave = false;

		break;

	case enWashing:		//皿を洗っているとき。

		m_skinModelRender->PlayAnimation(enanimationClip_Washing, m_transitionTime);
		m_animationClips[enanimationClip_Washing].SetLoopFlag(true);

		m_toHave = false;

		break;

	case enIdleHave:		//物をもって待機している。

		m_skinModelRender->PlayAnimation(enanimationClip_IdleHave, m_transitionTime);
		m_animationClips[enanimationClip_IdleHave].SetLoopFlag(true);

		m_toHave = true;

		if (stickPower.Length() > m_noLongerZero){			//移動した時。
			m_state = enRunHave;
		}

		SetFoodPosition();
		PutObjects(a);

		break;

	case enRunHave:		//物を持って走っている。

		m_skinModelRender->PlayAnimation(enanimationClip_RunHave, m_transitionTime);
		m_animationClips[enanimationClip_RunHave].SetLoopFlag(true);

		m_toHave = true;

		if (stickPower.Length() > m_noLongerZero == false) {		//移動してなかったとき。
			m_state = enIdleHave;
		}

		SetFoodPosition();
		PutObjects(a);

		break;

	}
}

void Player::SetFoodPosition()
{
	//todo 低　余裕があれば右手と左手のBoneの座標の中間地点にオブジェクトを置く処理にする。(アニメーションにオブジェクトがついてくるから)。
	m_objPos = m_ray;						//持っているものの座標にプレイヤーのレイ座標を代入。
	m_objPos.y += 60.f;						//気持ち上に座標を上げる。
	m_belongings->SetPosition(m_objPos);	//持っているオブジェクトの座標を設定。

}

void Player::PutObjects(int a)
{
	//todo 仮？。持ったものをおけるようになるまでのタイマー。
	m_putTimer -= 0.1f;

	if (g_pad[a].IsTrigger(enButtonA) && m_putTimer <= 0.f)		//Aボタンを押したときかつ、物を持ってから一定時間が経過した時。
	{
		if (m_objectAbove != nullptr) {					//物を置けるオブジェクトが目の前にあるとき。

			//オブジェクトに何も乗っていないとき。
			if (m_objectAbove->GetState() == 0) {		

				//持っているものが食べ物のとき。
				if (m_belongings->GetIndentValue() == 0) {		
					if (m_objNum == 1 || m_objNum == 4 || m_objNum == 7 || m_objNum == 8 || m_objNum == 9) {		//食べ物が置けるオブジェクトかどうか。
						m_objectAbove->PutThings(m_belongings);		//設置物の座標にオブジェクトの座標を代入。
						m_objectAbove->SetState(1);					//物を置いたオブジェクトのステートを変更する。
						m_state = enIdle;							//プレイヤーのステートを待機状態に。
					}
				}

				//持っているものが調理器具の場合。
				if (m_belongings->GetIndentValue() == 1) {		
					if (m_objNum == 1 || m_objNum == 5 || m_objNum == 7 || m_objNum == 8) {		//調理器具が置けるオブジェクトかどうか。
						m_objectAbove->PutThings(m_belongings);		//設置物の座標にオブジェクトの座標を代入。
						m_objectAbove->SetState(1);					//物を置いたオブジェクトのステートを変更する。
						m_state = enIdle;							//プレイヤーのステートを待機状態に。
					}
				}
			}

			//オブジェクトに何か乗っているとき。
			if (m_objectAbove->GetState() == 1){

				if (m_belongings->GetIndentValue() == 0) {			//持っているものが食べ物のとき。
					if (m_belongings->GetState() == 2) {			//持っているオブジェクトが切られているとき。
					//	m_objectAbove->TakeThings(m_belongings);	//乗っているオブジェクトを検索する。
						//todo 絶　乗っているものが調理器具だった場合、切ってあるものを置く。
						if (m_belongings->GetIndentValue() == 1) {
							//todo 絶　乗っている調理器具のKari関数を呼ぶ。そして持っているものを消す(条件付き)。
						}
					}
				}
			}
		}
		//todo メモ　ここのコメントを外すとどこにでも食べ物を置くことができる。
	//	else(m_state = enIdle);							//前方方向にオブジェクトがないとき。

		m_putTimer = 0.5f;		//タイマーを初期化。
	}
}

void Player::PickUpObjects(int a)
{
	if (g_pad[a].IsTrigger(enButtonA))						//Aボタンを押したとき。
	{
		if (m_objectAbove != nullptr) {						//目の前にオブジェクトがあるとき。
			if (m_objectAbove->GetState() == 1) {			//オブジェクトに何か乗っているとき。
				m_objectAbove->TakeThings(m_belongings);	//乗っているオブジェクトを検索。
				SetFoodPosition();							//持っているものの座標を指定。
				m_objectAbove->SetState(0);					//物をとったオブジェクトのステートを変更する。
				m_toHave = true;							//物を持つフラグ。
				m_state = enIdleHave;						//ステート変更。
			}
		}
	}
}

void Player::CuttingObject()
{
	//todo ゲージを描画して拡大率を操作する。　
//	m_gauge = NewGO<Gauge>(0, "gauge");
////	m_objectAbove->SetGaugePosition(m_gauge);
//	//todo 絶　圧倒的仮。
//	CVector3 hoge = m_position;
//	hoge.y -= 150.f;
//	m_gauge->SetPosition(hoge);
//
//	m_objectAbove->TakeThings(m_belongings);
//	m_gauge->Expansion();
//	if (m_gauge->GetScale()) {		//2D拡大率１なら。
		m_belongings->SetState(2);	//持てるものを切られている状態にする。
//	}
	
}

//todo 技　包丁をプレイヤーに持たせる。
void Player::HoldingKnife()
{
	int a;
	m_skelton = &m_skinModelRender->GetSkinModel().GetSkeleton();
	a = m_skelton->FindBoneID(L"Bone008");		//包丁を持つBoneの名前。
	Bone* m_bone;

	//座標を引き抜く。
	CVector3 pos;

	m_bone = m_skelton->GetBone(a);

	CMatrix pp;
	pp = m_bone->GetMatrix();
	pos.x = pp.m[3][0];
	pos.y = pp.m[3][1];
	pos.z = pp.m[3][2];

	CQuaternion rote;			//骨の回転を引き抜くよ。
	rote.SetRotation(pp);		//ボーンの行列から回転行列を抽出。
	
	if (m_knifeflag == false) {
		m_knife = NewGO<Knife>(0, "knife");
		m_knifeflag = true;
	}

	m_knife->SetPosition(pos);			//包丁に骨の座標を代入。
	m_knife->SetRotation(rote);			//包丁に骨の回転を代入。
}