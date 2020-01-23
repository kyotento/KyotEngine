#include "stdafx.h"
#include "Pot.h"
#include "StartCountdown.h"

namespace {
	float gaugeExpantionTime = 10.f;

	CVector3 checkPos;		//チェックマークの座標。
}

Pot::Pot()
{
	//調理器具と識別。
	m_identification = enKitchenWare;
}

Pot::~Pot()
{
	if (m_skinModelRender != nullptr) {
		DeleteGO(m_skinModelRender);		//スキンモデルを消す。
		m_skinModelRender = nullptr;
	}

	if (m_gauge != nullptr) {
		DeleteGO(m_gauge);					//ゲージを消す。
		m_gauge = nullptr;
	}

	DeleteLikeSoup();						//スープを消す処理。
}

bool Pot::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Pot/Pot.cmo");		//初期化、
	m_skinModelRender->SetPosition(m_position);						//座標指定。
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetSpecPower(2.f);							//スペキュラの値を設定。

	m_soupPos = m_position;			//スープの座標をお鍋の座標に代入。

	return true;
}

//スープが投入されたときの処理。
void Pot::Soup()
{
	//食べ物が二つ入っている状態。
	if (m_potState == enTwo) {							
		m_soupPos.y += 25.f;							//食べ物が入ったように見せるためにY座標を上げる。
		m_gauge->GaugeHalf();							//ゲージのスケールを半分にする。
		m_gauge->SetGaugeMax(false);				
		m_potState = enThree;							//食べ物が三つ入った状態にする。
	}

	//食べ物が一つ入っている状態のとき。
	if (m_potState == enOne) {							
		m_soupPos.y += 25.f;							//食べ物が入ったように見せるためにY座標を上げる。
		m_potState = enTwo;								//ポットに食べ物が二つ入っている状態。
		m_gauge->GaugeHalf();							//ゲージのスケールを半分にする。
	}

	//ポットに何も入っていないとき。
	if (m_potState == enZero) {							
		m_soupBase = NewGO<SoupBase>(0, "soup");		//スープの部分を生成する。	
		m_soupPos.x = m_position.x;						//鍋のX座標をスープのX座標に代入。
		m_soupPos.z = m_position.z;						//鍋のZ座標をスープのZ座標に代入。
		m_soupBase->SetPosition(m_soupPos);				//スープの座標を設定する。
		m_soupBase->DecideTheSoupType(m_putSoupFoods);	//生成するスープを決める。
		m_potState = enOne;								//ポットに食べ物が一つ入っている状態に。

		m_gauge = NewGO<Gauge>(0, "gauge");				//ゲージを生成する。
		m_gaugePos = m_position;						//ゲージの座標にお鍋の座標に代入。
		m_gaugePos.x -= 50.f;							//左に寄せる。
		m_gaugePos.y += 100.f;							//Y軸を少し上げてやる。
		m_gaugePos.z -= 70.f;							//少し手前に。
		m_gauge->SetPosition(m_gaugePos);				//ゲージの座標を指定。
	}
}

//todo 画像の切り替えをpotでやるのではなく、クラスを作ってやったほうがいいかも。

//スープを消す処理。
void Pot::DeleteLikeSoup()
{
	m_potState = enZero;			//状態を何も入っていない状態に。
	m_soupPos = m_position;			//座標を元に戻す。
	DeleteGO(m_soupBase);			//スープのモデルを消す。

	if (m_check != nullptr) {		//生成されていたら。
		DeleteGO(m_check);			//チェックマークを消す。
		m_check = nullptr;			//nullに。
	}
	if (m_danger != nullptr) {		//生成されていたら。
		DeleteGO(m_danger);			//危険マークを消す。
		m_sound->Stop();			//音を止める。
		m_danger = nullptr;			//nullに。
		m_dangerFlag = false;		//生成されていないのでfalseに変更する。
	}
	if (m_fire != nullptr) {		//生成されていたら。
		DeleteGO(m_fire);			//火事マークを消す。
		m_fire = nullptr;			//nullに。
		m_fireFlag = false;			//生成されていないのでfalseに変更する。
	}

	m_checkFlag = false;			//チェックマークフラグをfalseに。
	m_dangerStartTimer = 0.f;		//タイマーをリセット。
}

//状態変化。
void Pot::StateChange()
{
	//チェックマークの座標更新。
	checkPos = m_position;			//チェックマークの座標にお鍋の座標を代入。
	checkPos.y += 100.f;			//Y軸を少し上げてやる。
	checkPos.z -= 70.f;				//少し手前に。

	if (m_potState == enComplete)					//鍋の中身が完成しているとき。
	{
		DeleteGO(m_gauge);							//ゲージを消す。
		m_gauge = nullptr;							//ゲージのインスタンスをnullに。
		if (m_checkFlag == false) {					//チェックマークが生成されていないなら。
			m_check = NewGO<Check>(0, "check");		//チェックマークを生成。		
			m_check->SetPosition(checkPos);			//座標更新。
			m_checkFlag = true;						//チェック生成フラグをtrueに。
		}
		if (m_check != nullptr) {					//チェックマークのインスタンスが生成されているなr。
			m_check->SetPosition(checkPos);			//座標を更新。
		}
	}

	if (m_potState == enThree)						//食べ物が３個入っているとき。
	{
		if (m_gauge->GetGaugeMax()) {				//ゲージが最大値のとき。
			m_potState = enComplete;				//食べ物の状態を完成状態に。
		}
	}
}

//ゲージの拡大処理。(お鍋がコンロの上にある時のみ呼ばれる)。
void Pot::PotGaugeExpansion()
{
	StartCountdown* startCountDown = FindGO<StartCountdown>("startcountdown");
	if (startCountDown->GetGameStartFlag()) {				//ゲーム更新処理を開始していたら。
		if (m_gauge != nullptr) {							//ゲージが生成されていたら。
			m_gauge->Expansion(gaugeExpantionTime);			//ゲージの拡大処理。
		}
		if (m_check != nullptr || m_danger != nullptr) {
			m_dangerStartTimer += gametime().GetFrameDeltaTime();		//タイマーを更新。
		}
	}
}

//危険マーク描画処理。
void Pot::Danger2D()
{
	if (m_dangerFlag == false && m_dangerStartTimer >= 3.f && m_dangerStartTimer <= 10.f) {		//危険マークが生成されていない、且つタイマーが経過していた時。
		m_danger = NewGO<Danger>(0, "danger");			//画像を生成。
		checkPos = m_position;		//ゲージの座標にお鍋の座標に代入。
		checkPos.y += 100.f;		//Y軸を少し上げてやる。
		checkPos.z -= 70.f;			//少し手前に。
		m_danger->SetPosition(checkPos);				//座標更新。
		DeleteGO(m_check);								//チェックマークを消す。
		m_check = nullptr;								//チェックマークのインスタンスを消す。
		m_dangerFlag = true;							//生成フラグを返す。

		//危険音。
		m_sound = NewGO<Sound>(0, "sound");								//サウンドクラスを生成。
		m_sound->Init(L"Assets/sound/soundEffect/danger.wav", true);	//初期化。
		m_sound->SetVolume(0.5f);										//素材の音が大きかったので音量を変更。
		m_sound->Play();												//再生。
	}
	if (m_danger != nullptr) {							//危険マークが生成されているとき。
		checkPos = m_position;							//ゲージの座標にお鍋の座標に代入。
		checkPos.y += 100.f;							//Y軸を少し上げてやる。
		checkPos.z -= 70.f;								//少し手前に。
		m_danger->SetPosition(checkPos);				//座標更新。
	}
}

//火事マーク描画処理。
void Pot::Fire2D()
{
	if (m_fireFlag == false && m_dangerStartTimer > 10.f) {		//火事マークが生成されていない、且つタイマーが経過していた時。	
		m_fire = NewGO<Fire>(0, "fire");			//画像を生成。
		DeleteGO(m_danger);							//危険マークを消す。
		m_danger = nullptr;							//危険マークのインスタンスを消す。
		m_dangerFlag = false;						//生成されてないのでフラグを返す。
		m_fireFlag = true;							//生成フラグを返す。
		m_sound->Stop();							//危険音を止める。
	}
	if (m_fire != nullptr) {						//火事マークが生成されているとき。
		checkPos = m_position;						//ゲージの座標にお鍋の座標に代入。
		checkPos.y += 100.f;						//Y軸を少し上げてやる。
		checkPos.z -= 70.f;							//少し手前に。
		m_fire->SetPosition(checkPos);				//座標を更新。
	}
}

//ゲージの座標更新処理。
void Pot::GeugePosUpdate()
{
	//ゲージの座標更新。
	m_gaugePos = m_position;		//ゲージの座標にお鍋の座標に代入。
	m_gaugePos.x -= 50.f;			//左に寄せる。
	m_gaugePos.y += 100.f;			//Y軸を少し上げてやる。
	m_gaugePos.z -= 70.f;			//少し手前に。

	m_skinModelRender->SetPosition(m_position);		//座標を更新。
	m_skinModelRender->SetRotation(m_rotation);		//回転を更新。
	m_soupPos.x = m_position.x;						//鍋のX座標をスープのX座標に代入。
	m_soupPos.z = m_position.z;						//鍋のZ座標をスープのZ座標に代入。

	if (m_soupBase != nullptr) {						//スープが生成されていたら。
		m_soupBase->SetPosition(m_soupPos);				//スープの座標を指定。
	}
	if (m_gauge != nullptr) {							//ゲージが生成されていたら。
		m_gauge->SetPosition(m_gaugePos);				//ゲージの座標を指定。
	}
}

// お鍋に入っているお皿に載る予定の料理変更する。
void Pot::ChangeCuisine()
{
	if (m_putSoupFoods == Belongings::enTomato) {			//スープがトマトのとき。
		m_potDishCuisine = CookingList::enTomatoSoup;		//状態を変更。
	}
	if (m_putSoupFoods == Belongings::enOnion) {			//スープが玉ねぎのとき。
		m_potDishCuisine = CookingList::enOnionSoup;		//状態を変更。
	}
}

void Pot::Update()
{
	GeugePosUpdate();			//ゲージの座標更新処理。
	ChangeCuisine();			//お鍋に入っているお皿に載る予定の料理変更する。		
	StateChange();				//状態変化。
	Danger2D();					//危険マーク描画処理。
	Fire2D();					//火事マーク描画処理。
}