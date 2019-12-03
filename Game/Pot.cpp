#include "stdafx.h"
#include "Pot.h"


Pot::Pot()
{
	//調理器具と識別。
	m_identification = enKitchenWare;
}


Pot::~Pot()
{
	DeleteGO(m_skinModelRender);
}


bool Pot::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Pot/Pot.cmo");		//初期化、
	m_skinModelRender->SetPosition(m_position);						//座標指定。

	m_soupPos = m_position;

	return true;
}

//スープが投入されたときの処理。
void Pot::Soup()
{
	if (m_potState == enTwo) {						//食べ物が二つ入っている状態。
		m_soupPos.y += 25.f;							//食べ物が入ったように見せるためにY座標を上げる。
		m_potState = enThree;						//食べ物が三つ入った状態にする。
	}
	//todo 仮　三つ入った時完成形。
	if (m_potState == enThree)
	{
		m_potState = enComplete;
	}
	if (m_potState == enOne) {							//食べ物が一つ入っている状態のとき。
		m_soupPos.y += 25.f;							//食べ物が入ったように見せるためにY座標を上げる。
		m_potState = enTwo;								//ポットに食べ物が二つ入っている状態。
	}

	if (m_potState == enZero) {							//ポットに何も入っていないとき。
		m_soupBase = NewGO<SoupBase>(0, "soup");		//スープの部分を生成する。
		m_soupBase->DecideTheSoupType(m_putSoupFoods);
		m_potState = enOne;								//ポットに食べ物が一つ入っている状態に。
		m_gauge = NewGO<Gauge>(0, "gauge");				//ゲージを生成する。
		m_gauge->SetPosition(m_position);				//ゲージの座標を指定。
	}
}

void Pot::DeleteLikeSoup()
{
	m_potState = enZero;			//状態を何も入っていない状態に。
	m_soupPos = m_position;			//座標を元に戻す。
	DeleteGO(m_soupBase);			//スープのモデルを消す。
}

void Pot::Update()
{
	m_skinModelRender->SetPosition(m_position);		//座標を更新。
	m_soupPos.x = m_position.x;		//鍋のX座標をスープのX座標に代入。
	m_soupPos.z = m_position.z;		//鍋のZ座標をスープのZ座標に代入。
	m_gaugePos = m_position;		//ゲージの座標にお鍋の座標に代入。
	m_gaugePos.y += 100.f;			//Y軸を少し上げてやる。

	if (m_soupBase != nullptr) {						//スープが生成されていたら。
		m_soupBase->SetPosition(m_soupPos);				//スープの座標を指定。
	}

	if (m_gauge != nullptr) {							//ゲージが生成されていたら。
		m_gauge->SetPosition(m_gaugePos);				//ゲージの座標を指定。	
	//	m_gauge->Expansion();							//ゲージの拡大処理。
	}

}