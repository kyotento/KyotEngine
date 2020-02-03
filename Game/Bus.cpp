#include "stdafx.h"
#include "Bus.h"

//#define DEBUG			//デバッグ時定義する。
namespace {
	float a = 0;
	const float fallSpeed = 9.8f;				//落下速度。 
	const float moveSpeed = 10.f;				//移動速度。

	const float playerCollidedRadius = 45.f;			//カプセルコライダーの半径。
	const float playerCollidedHeight = 50.f;			//カプセルコライダーの高さ。

	CVector3 camerapos = { 0,900.f,-600.f };			//注視点からカメラの座標を指定するための値。
}

Bus::Bus()
{
}


Bus::~Bus()
{
	DeleteGO(m_skinModelRender);
}


bool Bus::Start()
{

	m_gameCamera = FindGO<GameCamera>("gamecamera");

	//バスのモデル生成諸々。
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/bus/bus.cmo");
	m_skinModelRender->InitNormalMap(L"Assets/sprite/bus_Normal.dds");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	m_resetPosition = m_position;			//初期座標をバックアップ。

	m_characon.Init(playerCollidedRadius, playerCollidedHeight, m_position);

	return true;
}

//移動処理。
void Bus::Move()
{
	m_stickPower.x = g_pad[0].GetLStickXF();		//左スティックのX軸の傾き。
	m_stickPower.y = 0.f;							//左スティックのY軸。
	m_stickPower.z = g_pad[0].GetLStickYF();		//左スティックのZ軸の傾き。

	m_move = m_stickPower * moveSpeed;				//移動速度の計算。
	m_move.y -= fallSpeed;							//落下速度の計算。
	m_position = m_characon.Execute(1.0, m_move);	//キャラコンに移動速度を代入。

	m_skinModelRender->SetPosition(m_position);
}

//回転処理。
void Bus::Rotation()
{
	CVector3 m_YisDie;
	m_YisDie = m_move;					//移動速度(方向持ち)を代入。
	m_YisDie.y = 0.0f;					//Y軸は必要ないので0を代入。
	m_YisDie.Normalize();				//正規化して向きを求める。
	m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(m_YisDie.x, m_YisDie.z));			//回転を計算。

	//移動していた場合のみ回転を更新する。
	if (m_YisDie.Length() > 0.01f) {							
		m_skinModelRender->SetRotation(m_rotation);			
	}
}

void Bus::Update()
{
	//デバッグ。
#ifdef DEBUG
	a += gametime().GetFrameDeltaTime();
	m_rotation.SetRotation(CVector3::AxisY(), 1);			//回転を計算。
	m_skinModelRender->SetRotation(m_rotation);

#endif
	//カメラを追従させる処理。
	m_gameCamera->SetTarget(m_position);
	CVector3 cameraPos = m_position + camerapos;
	m_gameCamera->SetPosition(cameraPos);

	Move();				//移動処理。
	Rotation();			//回転処理。
}