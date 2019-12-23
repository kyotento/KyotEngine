#include "stdafx.h"
#include "OrderGenerations.h"

namespace {
	float foodPosY = 320.f;
}

OrderGenerations::OrderGenerations()
{
}

OrderGenerations::~OrderGenerations()
{
}

bool OrderGenerations::Start()
{
	m_foodSheetGenerations = NewGO<FoodSheetGenerations>(3, "foodSheet");

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
		m_position[m_orderNumber].x = 540.f;			//X座標を指定。
		m_position[m_orderNumber].y = m_sheet_y;		//Y座標を指定。
		m_position[m_orderNumber].z = m_sheet_z;		//Z座標を指定。
		m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//座標を更新。

		m_generationNum += 1;		//生成数を加算する。
		m_orderNumber += 1;			//注文番号を変更する。
		m_order = false;			//生成されたのでフラグを返す。
	}
}

//移動処理。
void OrderGenerations::Move()
{
	for (int m_orderNumber = 0; m_orderNumber < m_orderNumLimit; m_orderNumber++) {		//配列の数分ループする。
		if (m_orderSheet[m_orderNumber] != nullptr) {			//シートが生成されていたら。
			if (m_position[m_orderNumber].x > m_moveLimit[m_orderNumber]) {		//座標が上限値に達していなかったら。
				m_position[m_orderNumber].x -= 20.f;				//X座標を更新。	
				m_position[m_orderNumber].y = m_sheet_y;		//Y座標を更新。
				m_position[m_orderNumber].z = m_sheet_z;		//Z座標を更新。
			}
			m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//シートの座標を更新。

			if (m_position[m_orderNumber].x <= m_moveLimit[m_orderNumber]) {	//座標が上限値に達した時。

				FoodSheetGeneration(1, m_orderNumber);		//１は仮。
				FoodSheetPosUpdate();						//食べ物シートの座標更新処理。
			}
			else{
			}
		}
	}
}

//料理に使用する食べ物を書くシート。
void OrderGenerations::FoodSheetGeneration(int FoodTypeNum, int genenum)
{
	if (m_foodSheetGenerationFlag == false) {		//食べ物シートを生成していなかったら。
		m_foodSheetGenerations->FoodSheetGeneration(FoodTypeNum);		//食べ物シートを生成。
		m_foodSheetGenerations->SetPosition(m_position[genenum]);		//生成されたシートの座標を指定してやる。
		foodPosY = m_position[genenum].y;								//Y座標を保存しておく。

		m_foodSheetGenerationFlag = true;			//生成した。
	}
}

//食べ物シートの座標更新処理。
void OrderGenerations::FoodSheetPosUpdate()
{
	foodPosY += -1.f;					//Y座標を枚フレーム更新。
	if (m_foodSheetGenerationFlag) {	//生成されていたら。
		m_foodSheetGenerations->SetPositionY(foodPosY);		//座標を更新する。
	}
}

void OrderGenerations::Update()
{
	//生成処理。
	Generations();
	//移動処理。
	Move();
}
