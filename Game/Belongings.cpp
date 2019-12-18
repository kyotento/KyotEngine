#include "stdafx.h"
#include "Belongings.h"
#include "Pot.h" 
#include "Dish.h"

Belongings::Belongings()
{

}


Belongings::~Belongings()
{
}

bool Belongings::Start()
{

	return true;
}

void Belongings::SetSoupBase(Belongings* puttingBelongings)
{
	Pot* pot = (Pot*)puttingBelongings;		//どのPotか検索をかける。	
	pot->Soup();				//スープの素を生成する。	
}

//スープを消す処理。
void Belongings::DeleteSoup(Belongings* belongings)
{
	Pot* pot = (Pot*)belongings;
	pot->DeleteLikeSoup();
}

int Belongings::GetPotFoosType(Belongings* powt)
{
	Pot* pot = (Pot*)powt;

	return	pot->GetPutSoupFoods();
}
void Belongings::SetPotFoodType(Belongings* powt, int fooType)
{
	Pot* pot = (Pot*)powt;
	pot->SetPutSoupFoods(fooType);
}

void Belongings::PotGaugeExpansion(Belongings* belongings)
{
	Pot* pot = (Pot*)belongings;
	pot->PotGaugeExpansion();
}

//お皿に食べ物を置く処理。
void Belongings::PutDishs(Belongings* belongings ,int FoodType)
{
	Dish* dish = (Dish*)belongings;
	dish->PutDish(FoodType);
}

// お皿洗い場の重ねてあるお皿からお皿を一つとる処理。
void Belongings::PutDishFromKitchen(Belongings* belongings, Kitchen* kitchen)
{
	Dish* dish = (Dish*)belongings;
	dish->DeleteDishList(kitchen);
}

// ゲージ生成、拡大、画像差し替えを担う関数。
void Belongings::GaugeGeneration(bool enlargedDivision, float time, float numberOfTimer, bool checkGeneration)
{
	if (m_GaugeGenerationFlag == false) {			//ゲージが生成されていなければ。
		m_gauge = NewGO<Gauge>(0, "gauge");			//ゲージを生成する。
		m_gaugePos = m_position;					//ゲージの座標にモデルの座標を代入。
		m_gaugePos.x -= 50.f;						//左に寄せる。
		m_gaugePos.y += 100.f;						//Y軸を少し上げてやる。
		m_gaugePos.z -= 70.f;						//少し手前に寄せる。	
		m_gauge->SetPosition(m_gaugePos);			//ゲージの座標を更新。
		m_GaugeGenerationFlag = true;				//ゲージが生成されたのでフラグを返す。
	}

	if (m_gauge != nullptr) {						//ゲージが生成されていたならば。
		if (enlargedDivision) {						//拡大分割をする場合。
			m_gauge->Magnification(time, numberOfTimer);			//ゲージを拡大する。
		}

		if (enlargedDivision == false) {			//拡大分割をしない場合。
			m_gauge->Expansion(time);				//ゲージを拡大する。
		}
	}

	if (m_gauge != nullptr && m_gauge->GetGaugeMax())			//ゲージが最大になったら。
	{
		if (m_identification == enFood) {			//食べ物のとき。
			m_foodState = enCutting;				//食べ物の状態を切られた状態に。
		}
		DeleteGO(m_gauge);							//ゲージを消す。
		m_gauge = nullptr;							//ゲージのインスタンスを消す。
		if (checkGeneration == false) {
			m_GaugeGenerationFlag = false;
		}
		if (checkGeneration) {						//ちぇっくまーくを生成する処理のとき。
			m_check = NewGO<Check>(0, "check");		//チェックマークを生成する。
			m_gaugePos = m_position;
			m_gaugePos.y += 100.f;			//Y軸を少し上げてやる。
			m_gaugePos.z -= 70.f;
			m_check->SetPosition(m_gaugePos);
		}
	}
}

//ゲージの座標更新。
void Belongings::GaugePosUpdate()
{
	if (m_gauge != nullptr)
	{
		m_gaugePos = m_position;
		m_gaugePos.x -= 50.f;			//左に寄せる。
		m_gaugePos.y += 100.f;			//Y軸を少し上げてやる。
		m_gaugePos.z -= 70.f;
		m_gauge->SetPosition(m_gaugePos);
	}

	if (m_check != nullptr) {
		m_gaugePos = m_position;
		m_gaugePos.y += 100.f;			//Y軸を少し上げてやる。
		m_gaugePos.z -= 70.f;
		m_check->SetPosition(m_gaugePos);
		m_checkDeleteTimer += 1.f / 60.f;

		if (m_checkDeleteTimer >= 1.f) {
			DeleteGO(m_check);
			m_check = nullptr;
		}
	}
}

void Belongings::DeleteGauge()
{
	DeleteGO(m_gauge);
	DeleteGO(m_check);
}

void Belongings::Update()
{

}
