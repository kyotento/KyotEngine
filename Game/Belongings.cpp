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

//todo そのうち持っている物ごとに生成するものを変える。(SoupBaseクラス側でやったほうがいいかもしれない。)
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

void Belongings::Update()
{

}
