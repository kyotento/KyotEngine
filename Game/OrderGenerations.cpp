#include "stdafx.h"
#include "OrderGenerations.h"

namespace {
	static int cuisinePriority = 5;		//料理画像の実行優先度。
	int deleteOrderNum = 5;			//消すシートの配列番号を保持する。

	int penalty = -30;				//時間制限以内に料理を持ってこれなかったときのスコアペナルティ。
	int foodScore = 60;				//料理を出したときのスコア。
	int chip = 0;					//チップ。

	float cuisineSize = 50.f;		//料理の画像のサイズ。
	float foodSize = 30.f;			//食べ物の画像のサイズ。
	float gaugeScale = 1.f;			//拡大率を格納する。
	float sheetMoveSpeed = 20.f;	//画像の移動速度。
}

OrderGenerations::OrderGenerations()
{
}

OrderGenerations::~OrderGenerations()
{
	DeleteGO(m_cookingList);							//料理リストを消す。
	for (int i = 0; i < m_orderNumLimit; i++) {
		DeleteGO(m_orderSheet[i]);						//注文シートを消す。
		DeleteGO(m_foodSheetGenerations[i]);			//食べ物シートを消す。
		DeleteGO(m_timeLimitGauge[i]);					//ゲージを消す。
		DeleteGO(m_spriteRenderCuisine[i]);				//料理の画像を消す。
		DeleteGO(m_spriteRenderFoods[i]);				//食べ物の画像を消す。
		DeleteGO(m_spriteRenderCuisineMethod[i]);		//調理方法の画像を消す。
	}	
}

bool OrderGenerations::Start()
{
	m_cookingList = NewGO<CookingList>(0, "cookingList");			//料理リストを生成。
	m_score = FindGO<Score>("score");								//スコアクラスのインスタンスを取得。
	m_startCountDown = FindGO<StartCountdown>("startcountdown");	//StartCountdownのインスタンスを取得。

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
		m_orderGenerationFlag = false;				//生成し終えてないのでフラグをfalseに。
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
		//	if (m_cuisineSheetFlag[m_orderNum] == false) {		//注文シートが生成されていないとき(一度も座標が上限値に達していないとき)。
				if (m_position[m_orderNum].x > m_moveLimit[m_orderNum]) {		//座標が上限値に達していなかったら。
					m_position[m_orderNum].x -= sheetMoveSpeed;		//X座標を更新。	
					m_position[m_orderNum].y = m_sheet_y;			//Y座標を更新。
					m_position[m_orderNum].z = m_sheet_z;			//Z座標を更新。
				}
				m_orderSheet[m_orderNum]->SetPosition(m_position[m_orderNum]);		//シートの座標を更新。
		//	}

			if (m_position[m_orderNum].x <= m_moveLimit[m_orderNum]) {	//座標が上限値に達した時。
				if (m_cuisineDecision[m_orderNum] == false) {			//料理が決定していないとき。
					m_dishName[m_orderNum] = m_cookingList->OrderSetting();			//料理をランダムに決める。
					m_cookingList->CookingInformations();							//料理の情報を格納。
					m_foodType[m_orderNum] = m_cookingList->GetFoodType();			//料理に必要な食べ物の種類を取得。
					m_cuisineDecision[m_orderNum] = true;				//料理が決定したのでフラグを返す。
				}

				FoodSheetGeneration(m_foodType[m_orderNum], m_orderNum);		//食べ物シートを生成する。
				FoodSheetPosUpdate(m_orderNum);							//食べ物シートの座標更新処理。
				m_timeLimitGauge[m_orderNum]->ChangeScale();			//ゲージの拡大処理。
			}
			
			/// <summary>
			/// 常に呼ばれる処理はここに書く。
			/// </summary>
			TimeLimitOrder(m_orderNum);			//時間制限を超えてしまった注文の処理。
		//	ShakeOrder(m_orderNum);				//注文票を揺らす処理。
			PositionUpdate(m_orderNum);			//座標更新。
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
		m_timeLimitGaugePosition[genenum].x -= 55.f;								//ゲージだけpivotが違うので少し左に移動する。
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

	if (m_foodSheetGenerationFlag[genenum]) {					//生成されていたら。
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
			m_orderGenerationFlag = true;				//一通り生成されたのでフラグを返す。
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
			m_orderGenerationFlag = true;				//一通り生成されたのでフラグを返す。
		}
	}
}

// 消す注文シートを判定する処理。
void OrderGenerations::JudgmentDeleteOrder()
{
	if (m_deliveryCuisine != CookingList::encookingListNum) {			//何か納品されたとき。
		for (int i = 0; i < m_orderNumLimit; i++) {			//注文シートの上限値分ループする。
			if (m_deliveryCuisine == m_dishName[i]) {		//配列に格納された料理と一致した時。
				m_kari[i] = m_dishName[i];		//ゲージ拡大率判定用配列に格納。
			}
		}

		//一度すべての注文を確認したうえでゲージの拡大率を比べて一番小さいものを消すため２回に処理を分けている。
		for (int i = 0; i < m_orderNumLimit; i++) {				//注文シートの上限値分ループする。
			if (m_kari[i] == m_deliveryCuisine) {				//配列に格納された料理と一致した時。
				if (m_timeLimitGauge[i] != nullptr) {			//ゲージが生成されているとき。
					if (gaugeScale > m_timeLimitGauge[i]->GetScale_X()) {		//もしｋよりもスケールが小さいとき。
						gaugeScale = m_timeLimitGauge[i]->GetScale_X();			//gaugeScaleに値を代入。
						deleteOrderNum = i;										//配列番号を代入。
					}
				}
			}
		}

		if (deleteOrderNum != m_orderNumLimit) {		//消す配列が指定されていたら(変更があった場合)。

			if (m_timeLimitGauge[deleteOrderNum]->GetGaugeState() == TimeLimitGauge::en66Then){			//消す配列のゲージの状態がen66Thenのとき。
				chip = 12;			//チップを指定(スコアの20％分)。
			}
			if(m_timeLimitGauge[deleteOrderNum]->GetGaugeState() == TimeLimitGauge::en33Then) {			//消す配列のゲージの状態がen33Thenのとき。
				chip = 6;			//チップを指定(スコアの10％分)。
			}

			m_score->AddProfit(foodScore);				//チップ加算前のスコアを加算。
			m_score->AddChip(chip);						//チップを加算。

			foodScore += chip;							//スコアにチップを加算。
			m_score->AddScore(foodScore);				//スコアを加算。
			foodScore = 60.f;							//スコアを基本値に戻す。
			DeleteOrder(deleteOrderNum);				//一致した配列の注文シートを消す。
		}

		m_delivery->SetDeliveryDishCuisine(CookingList::encookingListNum);			//受け渡し口の受け取った料理をリセットする。
		gaugeScale = 1.f;			//拡大率をリセット。

		for (int i = 0; i < m_orderNumLimit; i++) {					//注文シートの配列分ループする。
			m_kari[i] = CookingList::encookingListNum;				//配列をリセットする。
		}
	}
}

//注文票を消す処理。
void OrderGenerations::DeleteOrder(int genenum)
{
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

	//注文票を消した後の処理。
	DeleteOrderAfter(genenum);

}

//注文票を消した後の処理。
void OrderGenerations::DeleteOrderAfter(int genenum)
{
	for (int i = genenum; i < m_orderNumLimit; i++) {			//注文シートの上限値分ループする。ループを、消去した注文シートの配列からに。
		int Limit = m_orderNumLimit;
	//	if (i <= (Limit -= 2)) {		//配列の上限値より1小さい値の場合。
		if(m_dishName[i+1] != CookingList::encookingListNum && i <= (Limit -= 2)){			//次の配列がnullでないとき、且つ一番後ろの配列でないとき。
			//各画像の配列をずらす。
			m_orderSheet[i] = m_orderSheet[i + 1];
			m_timeLimitGauge[i] = m_timeLimitGauge[i + 1];
			m_foodSheetGenerations[i] = m_foodSheetGenerations[i + 1];
			m_spriteRenderCuisine[i] = m_spriteRenderCuisine[i + 1];
			m_spriteRenderFoods[i] = m_spriteRenderFoods[i + 1];
			m_spriteRenderCuisineMethod[i] = m_spriteRenderCuisineMethod[i + 1];
			m_dishName[i] = m_dishName[i + 1];			//注文された料理を格納。
		}	

		if (m_dishName[i + 1] == CookingList::encookingListNum || i >= (Limit += 1)) {		//次の配列がnullのとき、又は配列の一番後ろのとき。
			//各画像のインスタンスを破棄。
			m_orderSheet[i] = nullptr;
			m_timeLimitGauge[i] = nullptr;
			m_foodSheetGenerations[i] = nullptr;
			m_spriteRenderCuisine[i] = nullptr;
			m_spriteRenderFoods[i] = nullptr;
			m_spriteRenderCuisineMethod[i] = nullptr;
			m_dishName[i] = CookingList::encookingListNum;		//コピーし終わった注文シートの料理を破棄。

			m_generationNum -= 1;		//生成数を減算する。
			m_orderNumber -= 1;			//注文番号を変更する。
			m_cuisineSheetFlag[i] = false;					//食べ物シートを生成していない状態に。
			m_foodSheetGenerationFlag[i] = false;			//食べ物シートを生成していない状態に。
			m_cuisineDecision[i] = false;					//料理が決定していない状態に。
			i = m_orderNumLimit;		//ループしないように上限値を代入。
		}
	}
}

//時間制限をこえてしまった注文の処理。
void OrderGenerations::TimeLimitOrder(int genenum)
{
	if (m_timeLimitGauge[genenum] != nullptr) {				//ゲージが生成されているとき。
		if (m_timeLimitGauge[genenum]->GetTimeLimitFlag() == true) {			//時間制限が来た時。
			m_timeLimitGauge[genenum]->SetScale(1.f);				//画像のスケールを１に戻す。
			m_timeLimitGauge[genenum]->SetTimeLimitFlag(false);
			//スコアにペナルティを加算する。
			m_score->AddScore(penalty);
			m_score->AddPenalty(penalty);			//ペナルティを加算。
		}
	}
}

//注文票を揺らす処理。
void OrderGenerations::ShakeOrder(int genenum)
{
	if (m_timeLimitGauge[genenum] != nullptr) {
		if (m_timeLimitGauge[genenum]->GetGaugeState() == TimeLimitGauge::en10Less) {		//ゲージの状態が拡大率１０パーセント以下のとき。
			//todo 仮　カリカリの仮。
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

//画像の座標更新処理。
void OrderGenerations::PositionUpdate(int genenum)
{
	if (m_cuisineSheetFlag[genenum] == true) {			//食べ物シートが生成されていたら。
		//各画像の座標を更新する。
		m_foodSheetPosition[genenum].x = m_position[genenum].x;
		m_foodSheetGenerations[genenum]->SetPosition(m_foodSheetPosition[genenum]);
		m_timeLimitGaugePosition[genenum].x = m_position[genenum].x ;
		m_timeLimitGaugePosition[genenum].x -= 55.f;
		m_timeLimitGauge[genenum]->SetPosition(m_timeLimitGaugePosition[genenum]);
		m_spriteRenderCuisine[genenum]->SetPosition(m_position[genenum]);
		m_spriteRenderFoods[genenum]->SetPosition(m_foodSheetPosition[genenum]);
		m_kitchenWarePosition[genenum].x = m_position[genenum].x;
		m_spriteRenderCuisineMethod[genenum]->SetPosition(m_kitchenWarePosition[genenum]);
	}
}

void OrderGenerations::Update()
{
	if (m_startCountDown->GetGameStartFlag()) {			//ゲーム更新処理を開始していたら。
		//生成処理。
		Generations();
		//移動処理。
		Move();
		//注文シートを消す処理。
		JudgmentDeleteOrder();

		if (m_delivery == nullptr) {										//受け渡し口のインスタンスがないなら。
			m_delivery = FindGO<Delivery>("delivery");						//受け渡し口のインスタンスを検索する。
		}
		if (m_orderGenerationFlag) {										//注文シートを一通り生成し終えたなら。
			m_deliveryCuisine = m_delivery->GetDeliveryDishCuisine();		//納品された料理を検索して代入する。
		}
	}
}

