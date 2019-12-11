#include "stdafx.h"
#include "Pot.h"


Pot::Pot()
{
	//調理器具と識別。
	m_identification = enKitchenWare;
}


Pot::~Pot()
{
//	DeleteGO(m_skinModelRender);
}


bool Pot::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Pot/Pot.cmo");		//初期化、
	m_skinModelRender->SetPosition(m_position);						//座標指定。

	m_soupPos = m_position;			//スープの座標をお鍋の座標に代入。

	return true;
}

//スープが投入されたときの処理。
void Pot::Soup()
{
	if (m_potState == enTwo) {						//食べ物が二つ入っている状態。
		m_soupPos.y += 25.f;						//食べ物が入ったように見せるためにY座標を上げる。
		m_gauge->GaugeHalf();						//ゲージのスケールを半分にする。
		m_potState = enThree;						//食べ物が三つ入った状態にする。
	}

	if (m_potState == enOne) {							//食べ物が一つ入っている状態のとき。
		m_soupPos.y += 25.f;							//食べ物が入ったように見せるためにY座標を上げる。
		m_potState = enTwo;								//ポットに食べ物が二つ入っている状態。
		m_gauge->GaugeHalf();							//ゲージのスケールを半分にする。
	}

	if (m_potState == enZero) {							//ポットに何も入っていないとき。
		m_soupBase = NewGO<SoupBase>(0, "soup");		//スープの部分を生成する。
		m_soupBase->DecideTheSoupType(m_putSoupFoods);	//生成するスープを決める。
		m_potState = enOne;								//ポットに食べ物が一つ入っている状態に。
		m_gauge = NewGO<Gauge>(0, "gauge");				//ゲージを生成する。
		m_gauge->SetPosition(m_gaugePos);				//ゲージの座標を指定。
	}
}

void Pot::DeleteLikeSoup()
{
	m_potState = enZero;			//状態を何も入っていない状態に。
	m_soupPos = m_position;			//座標を元に戻す。
	DeleteGO(m_soupBase);			//スープのモデルを消す。
	DeleteGO(m_check);				//チェックマークを消す。
	m_check = nullptr;		
	m_checkFlag = false;			//チェックマークフラグをfalseに。
}

//状態変化。
void Pot::StateChange()
{
	if (m_potState == enComplete)					//鍋の中身が完成しているとき。
	{
		DeleteGO(m_gauge);							//ゲージを消す。
		m_gauge = nullptr;							//ゲージのインスタンスをnullに。
		if (m_checkFlag == false) {
			m_check = NewGO<Check>(0, "check");		//チェックマークを生成。
			m_check->SetPosition(m_position);		//座標を更新。
			m_checkFlag = true;						//チェック生成フラグをtrueに。
		}
	}

	if (m_potState == enThree)						//食べ物が３個入っているとき。
	{
		if (m_gauge->GetGaugeMax()) {				//ゲージが最大値のとき。
			m_potState = enComplete;				//食べ物の状態を完成状態に。
		}
	}
}

void Pot::PotGaugeExpansion()
{
	if (m_gauge != nullptr) {							//ゲージが生成されていたら。
		m_gauge->SetPosition(m_gaugePos);				//ゲージの座標を指定。	
		//todo 絶 コンロに載っているとき。
		m_gauge->Expansion(10.f);						//ゲージの拡大処理。
	}
}

void Pot::Update()
{
	m_skinModelRender->SetPosition(m_position);		//座標を更新。
	m_soupPos.x = m_position.x;		//鍋のX座標をスープのX座標に代入。
	m_soupPos.z = m_position.z;		//鍋のZ座標をスープのZ座標に代入。
	m_gaugePos = m_position;		//ゲージの座標にお鍋の座標に代入。
	m_gaugePos.x -= 50.f;
	m_gaugePos.y += 100.f;			//Y軸を少し上げてやる。
	m_gaugePos.z -= 70.f;

	if (m_soupBase != nullptr) {						//スープが生成されていたら。
		m_soupBase->SetPosition(m_soupPos);				//スープの座標を指定。
	}

	StateChange();										//状態変化。
}