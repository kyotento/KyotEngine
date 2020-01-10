#include "stdafx.h"
#include "OrderGenerations.h"

namespace {
	int cuisinePriority = 5;		//料理画像の実行優先度。

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
//	m_foodSheetGenerations = NewGO<FoodSheetGenerations>(0, "foodSheet");
	m_cookingList = NewGO<CookingList>(0, "cookingList");

	return true;
}

//生成処理。
void OrderGenerations::Generations()
{
	if (m_generationNum < m_orderNumLimit && m_order == false) {		//注文の数が上限値より少ないとき。且つ、注文が来ていないとき。
		m_orderTimer += 1.f / 60.f;					//タイマーを進める。
		if (m_orderTimer >= 10.f) {					//10秒以上経過したなら。
			m_order = true;							//注文フラグを返す。
			m_orderTimer = 0.f;						//タイマーをリセットする。
		}
	}

	if (m_order) {			//注文フラグがtrueなら。
		m_orderSheet[m_orderNumber] = NewGO<OrderSheet>(0, "orderSheet");		//配列m_order番目に注文シートを生成。
		m_position[m_orderNumber].x = m_sheet_x;		//X座標を指定。
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
	for (int m_orderNum = 0; m_orderNum < m_orderNumLimit; m_orderNum++) {		//配列の数分ループする。
		if (m_orderSheet[m_orderNum] != nullptr) {				//シートが生成されていたら。
			if (m_cuisineSheetFlag[m_orderNum] == false) {		//注文シートが生成されていないとき(一度も座標が上限値に達していないとき)。
				if (m_position[m_orderNum].x > m_moveLimit[m_orderNum]) {		//座標が上限値に達していなかったら。
					m_position[m_orderNum].x -= 20.f;			//X座標を更新。	
					m_position[m_orderNum].y = m_sheet_y;		//Y座標を更新。
					m_position[m_orderNum].z = m_sheet_z;		//Z座標を更新。
				}
				m_orderSheet[m_orderNum]->SetPosition(m_position[m_orderNum]);		//シートの座標を更新。
			}

			if (m_position[m_orderNum].x <= m_moveLimit[m_orderNum]) {	//座標が上限値に達した時。
				if (m_cuisineDecision[m_orderNum] == false) {			//料理が決定していないとき。
					m_dishName[m_orderNum] = m_cookingList->OrderSetting();			//料理をランダムに決める。
					m_cookingList->CookingInformations();							//料理の情報を格納。
					m_foodType[m_orderNum] = m_cookingList->GetFoodType();			//料理に必要な食べ物の種類を取得。
					m_cuisineDecision[m_orderNum] = true;				//料理が決定したのでフラグを返す。
				}

				FoodSheetGeneration(m_foodType[m_orderNum], m_orderNum);		//食べ物シートを生成する。
				FoodSheetPosUpdate(m_orderNum);						//食べ物シートの座標更新処理。
				m_timeLimitGauge[m_orderNum]->ChangeScale();			//ゲージの拡大処理。
			}
			
			/// <summary>
			/// 常に呼ばれる処理はここに書く。
			/// </summary>
			DeleteOrder(m_orderNum);			//シートを消す処理。
			TimeLimitOrder(m_orderNum);			//時間制限を超えてしまった注文の処理。
		//	ShakeOrder(m_orderNum);				//注文票を揺らす処理。
		//	PositionUpdate(m_orderNum);			//座標更新。
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
		m_foodSheetGenerations[genenum] = NewGO<FoodSheetGenerations>(0, "foodsheetgenerations");
		m_foodSheetGenerations[genenum]->FoodSheetGeneration(FoodTypeNum);			//食べ物シートを生成。
		m_foodSheetGenerations[genenum]->SetPosition(m_position[genenum]);			//生成されたシートの座標を指定してやる。
		m_foodPosY[genenum] = m_position[genenum].y;								//Y座標を保存しておく。

		m_timeLimitGauge[genenum] = NewGO<TimeLimitGauge>(0, "timelimitgauge");		//ゲージ生成。
		m_timeLimitGaugePosition[genenum] = m_position[genenum];					//シートの座標を代入。
		m_timeLimitGaugePosition[genenum].x -= 55.f;								//ゲージだけpovotが違うので少し左に移動する。
		m_timeLimitGaugePosition[genenum].y += 20.f;								//少し上に。
		m_timeLimitGauge[genenum]->SetPosition(m_timeLimitGaugePosition[genenum]);	//座標更新処理。

		m_foodSheetGenerationFlag[genenum] = true;			//生成したのでフラグを返す。
	}
}

//食べ物シートの座標更新処理。
void OrderGenerations::FoodSheetPosUpdate(int genenum)
{
	if (m_foodPosY[genenum] >= m_foodPosYLimit) {		//座標が上限値に達していないなら。
		m_foodPosY[genenum] += -1.f;					//Y座標を毎フレーム更新。
	}

	if (m_foodPosY[genenum] < m_foodPosYLimit) {	//上限値に達したら。
		Order(genenum);		//その他画像生成処理。
	}

	if (m_foodSheetGenerationFlag) {					//生成されていたら。
		m_foodSheetGenerations[genenum]->SetPositionY(m_foodPosY[genenum]);		//座標を更新する。
	}
}

//その他画像の生成処理。
void OrderGenerations::Order(int genenum)
{
	if (m_cuisineSheetFlag[genenum] == false) {			//料理の画像が生成されていないとき。
		if (m_cookingList->GetCookingList() == CookingList::enTomatoSoup){		//作成するものがトマトスープの場合。

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

		if (m_cookingList->GetCookingList() == CookingList::enOnionSoup){		//作成するものが玉ねぎスープのとき。

			//玉ねぎスープの画像を描画する。
			m_spriteRenderCuisine[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");						//料理の画像生成。
			m_spriteRenderCuisine[genenum]->Init(L"Assets/sprite/OnionSoup.dds", cuisineSize, cuisineSize);			//初期化。
			m_spriteRenderCuisine[genenum]->SetPosition(m_position[genenum]);										//座標更新。

			m_spriteRenderFoods[genenum] = NewGO<SpriteRender>(cuisinePriority, "sprite");							//食材の画像生成。
			m_spriteRenderFoods[genenum]->Init(L"Assets/sprite/Onion.dds", foodSize, foodSize);						//初期化。
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

//注文票を消す処理。
void OrderGenerations::DeleteOrder(int genenum)
{
	if (m_timeLimitGauge[genenum] != nullptr) {				//ゲージが生成されているとき。
		if (m_timeLimitGauge[genenum]->GetTimeLimitFlag() == true) {			//todo 仮　時間制限が来た時。
			DeleteGO(m_timeLimitGauge[genenum]);				//ゲージを消す
			m_timeLimitGauge[genenum] = nullptr;				//ゲージのインスタンスを破棄。
			DeleteGO(m_orderSheet[genenum]);					//注文シートを消す。
			m_orderSheet[genenum] = nullptr;					//注文シートのインスタンスを破棄。
			DeleteGO(m_foodSheetGenerations[genenum]);			//食べ物シートを消す。
			m_foodSheetGenerations[genenum] = nullptr;			//食べ物シートのインスタンスを破棄。
			DeleteGO(m_spriteRenderCuisine[genenum]);			//料理の画像を消す。
			m_spriteRenderCuisine[genenum] = nullptr;			//料理の画像のインスタンスを破棄。
			DeleteGO(m_spriteRenderFoods[genenum]);				//食材の画像を消す。
			m_spriteRenderFoods[genenum] = nullptr;				//食材の画像のインスタンスを破棄
			DeleteGO(m_spriteRenderCuisineMethod[genenum]);		//調理方法の画像を消す。
			m_spriteRenderCuisineMethod[genenum] = nullptr;		//調理方法の画像のインスタンスを破棄。
		}
	}
}

//じかんせいげんをこえてしまった注文の処理。
void OrderGenerations::TimeLimitOrder(int genenum)
{
	if (m_timeLimitGauge[genenum] != nullptr) {				//ゲージが生成されているとき。
		if (m_timeLimitGauge[genenum]->GetTimeLimitFlag() == true) {			//時間制限が来た時。
			m_timeLimitGauge[genenum]->SetScale(1.f);				//画像のスケールを１に戻す。
		}
	}
}

//注文票を揺らす処理。
void OrderGenerations::ShakeOrder(int genenum)
{
	if (m_timeLimitGauge[genenum] != nullptr) {
		if (m_timeLimitGauge[genenum]->GetGaugeState() == TimeLimitGauge::en10Less) {		//ゲージの状態が拡大率１０パーセント以下のとき。
			//for (int i = 0; i <= 3; i++) {
			//	if (i == 0) {
			//		m_position[genenum].x += 5.f;
			//	}
			//	if (i == 1) {
			//		m_position[genenum].x -= 5.f;
			//	}
			//	if (i == 2) {
			//		m_position[genenum].x -= 5.f;
			//	}
			//	if (i == 3) {
			//		m_position[genenum].x += 5.f;
			//		i = 0;
			//	}
			//	m_orderSheet[genenum]->SetPosition(m_position[genenum]);			//生成されたシートの座標を指定してやる。
			//}
		}
	}
}

void OrderGenerations::PositionUpdate(int genenum)
{
	m_foodSheetPosition[genenum].x = m_position[genenum].x;
	m_foodSheetPosition[genenum].y = m_foodPosY[genenum];
	m_foodSheetPosition[genenum].z = m_position[genenum].z;
}

void OrderGenerations::Update()
{
	//生成処理。
	Generations();
	//移動処理。
	Move();

	m_delivery = FindGO<Delivery>("delivery");				//受け渡し口のインスタンスを検索する。
	m_deliveryCuisine = m_delivery->GetDeliveryDishCuisine();		//納品された料理を検索して代入する。
}

//todo 配列ごと消すときにやること
/*
	生成フラグを返す。
	配列の空いたところを詰める。
	m_foodPosYをリセットする。
*/
