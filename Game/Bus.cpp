#include "stdafx.h"
#include "Bus.h"

//#define DEBUG			//デバッグ時定義する。
namespace {
	float a = 0;
	const float fallSpeed = 9.8f;				//落下速度。 
	const float moveSpeed = 10.f;				//移動速度。
	const float judgmentDistance = 100.f;		//旗との判定距離。

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
	m_skinModelRender->InitSpecMap(L"Assets/sprite/bus_spec.dds");
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

//カメラを追従させる処理。
void Bus::FollowCamera()
{
	m_gameCamera->SetTarget(m_position);
	CVector3 cameraPos = m_position + camerapos;
	m_gameCamera->SetPosition(cameraPos);
}

//旗に検索をかける処理諸々。
void Bus::FlagSearch()
{
	//旗のインスタンスを取得。
	m_flag[0] = FindGO<Flag>("flag1");
	m_flag[1] = FindGO<Flag>("flag2");
	m_flag[2] = FindGO<Flag>("flag3");

	//詳細画像生成用クラスのインスタンスを取得する。
	m_stageSelectDetailed = FindGO<StageSelectDetailed>("stageselectdetailed");
 
	//旗との距離判定をとる。
	for (int i = 0; i < FLAG_NUM; i++) {
		CVector3 vectorLength;			//旗とバスの距離格納用。
		vectorLength = m_position - m_flag[i]->GetPosition();		

		//一定距離以内だった場合。
		if (vectorLength.Length() < judgmentDistance) {
			m_flag[i]->NewButton();
			m_stageSelectDetailed->NewDetailedImage(i);		//イメージ画像を生成。
		}
		//範囲外だった時。
		else{
			m_flag[i]->DeleteButton();
		}

	}
	//すべての旗が範囲外のとき。
	if ((m_position - m_flag[0]->GetPosition()).Length() > judgmentDistance
		&& (m_position - m_flag[1]->GetPosition()).Length() > judgmentDistance
		&& (m_position - m_flag[2]->GetPosition()).Length() > judgmentDistance) {
		m_stageSelectDetailed->DeleteDetailedImage();
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

	FollowCamera();		//カメラを追従させる処理。
	Move();				//移動処理。
	Rotation();			//回転処理。
	FlagSearch();		//旗に検索をかける処理諸々。
}