#include "stdafx.h"
#include "OrderGenerations.h"

namespace {
	int cuisinePriority = 5;		//料理画像のプライオリティ。

	float cuisineSize = 50.f;		//料理の画像のサイズ。
	float foodSize = 30.f;			//食べ物の画像のサイズ。
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
	m_cookingList = NewGO<CookingList>(0, "cookingList");

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
				m_position[m_orderNumber].x -= 20.f;			//X座標を更新。	
				m_position[m_orderNumber].y = m_sheet_y;		//Y座標を更新。
				m_position[m_orderNumber].z = m_sheet_z;		//Z座標を更新。
			}
			m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//シートの座標を更新。

			if (m_position[m_orderNumber].x <= m_moveLimit[m_orderNumber]) {	//座標が上限値に達した時。

				FoodSheetGeneration(m_cookingList->GetFoodType(), m_orderNumber);		//食べ物シートを生成する。
				FoodSheetPosUpdate(m_orderNumber);						//食べ物シートの座標更新処理。
			}
		}
	}
}

//料理に使用する食べ物を書くシート。
void OrderGenerations::FoodSheetGeneration(int FoodTypeNum, int genenum)
{
	//座標更新処理。
	m_foodSheetPosition[genenum].x = m_position[genenum].x;
	m_foodSheetPosition[genenum].y = m_foodPosY[genenum];
	m_foodSheetPosition[genenum].z = m_position[genenum].z;

	if (m_foodSheetGenerationFlag[genenum] == false) {		//食べ物シートを生成していなかったら。
		m_foodSheetGenerations->FoodSheetGeneration(FoodTypeNum);		//食べ物シートを生成。
		m_foodSheetGenerations->SetPosition(m_position[genenum]);		//生成されたシートの座標を指定してやる。
		m_foodPosY[genenum] = m_position[genenum].y;								//Y座標を保存しておく。

		m_timeLimitGauge[genenum] = NewGO<TimeLimitGauge>(0, "timelimitgauge");
		m_timeLimitGaugePosition[genenum] = m_position[genenum];
		m_timeLimitGaugePosition[genenum].x -= 55.f;
		m_timeLimitGaugePosition[genenum].y += 20.f;
		m_timeLimitGauge[genenum]->SetPosition(m_timeLimitGaugePosition[genenum]);

		m_foodSheetGenerationFlag[genenum] = true;			//生成したのでフラグを返す。
	}
}

//食べ物シートの座標更新処理。
void OrderGenerations::FoodSheetPosUpdate(int genenum)
{
	if (m_foodPosY[genenum] >= m_foodPosYLimit) {		//座標が上限値に達していないなら。
		m_foodPosY[genenum] += -1.f;					//Y座標を毎フレーム更新。
	}

	else {		//上限値に達したら。
		Order(genenum);		//その他画像生成処理。
	}

	if (m_foodSheetGenerationFlag) {					//生成されていたら。
		m_foodSheetGenerations->SetPositionY(m_foodPosY[genenum]);		//座標を更新する。
	}
}

//その他画像の生成処理。
void OrderGenerations::Order(int genenum)
{
	if (m_cuisineSheetFlag[genenum] == false) {			//料理の画像が生成されていないとき。
		if (m_cookingList->GetCookingList() == CookingList::enTomatoSoup)		//作成するものがトマトスープの場合。
		{
			//トマトスープの画像を描画する。
			m_spriteRenderCuisine[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");						//料理の画像生成。
			m_spriteRenderCuisine[genenum]->Init(L"Assets/sprite/TomatoSoup.dds", cuisineSize, cuisineSize);		//初期化。
			m_spriteRenderCuisine[genenum]->SetPosition(m_position[genenum]);										//座標更新。

			m_spriteRenderFoods[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");							//食材の画像生成。
			m_spriteRenderFoods[genenum]->Init(L"Assets/sprite/Tomato.dds", foodSize, foodSize);					//初期化。
			m_spriteRenderFoods[genenum]->SetPosition(m_foodSheetPosition[genenum]);								//座標更新。

			m_spriteRenderCuisineMethod[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");					//調理方法の画像生成。
			m_spriteRenderCuisineMethod[genenum]->Init(L"Assets/sprite/pot.dds", foodSize, foodSize);				//初期化。
			m_kitchenWarePosition[genenum] = m_foodSheetPosition[genenum];											//シートの座標を代入。
			m_kitchenWarePosition[genenum].y -= 25.f;																//少し下に座標を移動。
			m_spriteRenderCuisineMethod[genenum]->SetPosition(m_kitchenWarePosition[genenum]);						//座標更新。

			m_cuisineSheetFlag[genenum] = true;			//料理の画像が生成されたのでフラグを返す。
		}
	}
}

void OrderGenerations::Update()
{
	//生成処理。
	Generations();
	//移動処理。
	Move();
}

//todo 配列ごと消すときにやること
/*
	生成フラグを返す。
	配列の空いたところを詰める。
	m_foodPosYをリセットする。
*/