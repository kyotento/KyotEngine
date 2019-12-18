#include "stdafx.h"
#include "OrderGenerations.h"

namespace {
	float m_sheet_x = 600.f;
	float m_sheet_y = 310.f;
	float m_sheet_z = 0.f;
	float moveLimit = -540.f;
}

OrderGenerations::OrderGenerations()
{
}

OrderGenerations::~OrderGenerations()
{
}

bool OrderGenerations::Start()
{

	return true;
}

//生成処理。
void OrderGenerations::Generations()
{
	if (m_generationNum < m_orderNumLimit && m_order == false) {		//注文の数が上限値より少ないとき。且つ、注文が来ていないとき。
		m_orderTimer += 1.f / 60.f;					//タイマーを進める。
		if (m_orderTimer >= 5.f) {					//5秒以上経過したなら。
			m_order = true;							//注文フラグを返す。
			m_orderTimer = 0.f;						//タイマーをリセットする。
		}
	}

	if (m_order) {			//注文フラグがtrueなら。
		m_orderSheet[m_orderNumber] = NewGO<OrderSheet>(0, "orderSheet");		//配列m_order番目に注文シートを生成。
		m_position[m_orderNumber].x = 540.f;
		m_position[m_orderNumber].x = m_sheet_y;
		m_position[m_orderNumber].x = m_sheet_z;
		m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//座標を更新。

		m_generationNum += 1;			//生成数を加算する。
		m_order = false;			//生成されたのでフラグを返す。
	}
}

void OrderGenerations::Move()
{
	if (m_orderSheet[m_orderNumber] != nullptr) {
		if (m_position[m_orderNumber].x > moveLimit) {
			m_position[m_orderNumber].x -= 5.f;
			m_position[m_orderNumber].y = m_sheet_y;
			m_position[m_orderNumber].z = m_sheet_z;
		}
		m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);
	}
}

void OrderGenerations::Update()
{
	//生成処理。
	Generations();
	//移動処理。
	Move();
}
