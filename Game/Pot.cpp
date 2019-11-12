#include "stdafx.h"
#include "Pot.h"


Pot::Pot()
{
}


Pot::~Pot()
{
	DeleteGO(m_skinModelRender);
}


bool Pot::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Pot/Pot.cmo");		//初期化、
	m_skinModelRender->SetPosition(m_position);						//座標指定。

	return true;
}

void Pot::Soup()
{

	if (m_potState == enTwo) {
		m_soupPos.y += 100.f;
		m_potState = enComplete;
	}
	if (m_potState == enOne) {							//食べ物が一つ入っている状態のとき。
		m_soupPos.y += 100.f;							//食べ物が冷えたように見せるためにY座用を上げる。
		m_potState = enTwo;								//ポットに食べ物が二つ入っている状態。
	}

	if (m_potState == enZero) {							//ポットに何も入っていないとき。
		m_soupBase = NewGO<SoupBase>(0, "soup");		//スープの部分を生成する。
		m_potState = enOne;								//ポットに食べ物が一つ入っている状態に。
	}
}

void Pot::Update()
{
	m_skinModelRender->SetPosition(m_position);		//座標を更新。
	if (m_soupBase != nullptr) {
		m_soupBase->SetPosition(m_soupPos);				//スープの座標を指定。
	}
	//m_soupPos = m_position;		//鍋の座標をスープの座標に代入。
}