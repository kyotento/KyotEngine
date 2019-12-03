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
void Belongings::SetSoupBase(Belongings* belongings)
{
	Pot* pot = (Pot*)belongings;		//どのPotか検索をかける。	
	pot->Soup(belongings);				//スープの素を生成する。	
}

//スープを消す処理。
void Belongings::DeleteSoup(Belongings* belongings)
{
	Pot* pot = (Pot*)belongings;
	pot->DeleteLikeSoup();
}

//お皿に食べ物を置く処理。
void Belongings::PutDishs(Belongings* belongings)
{
	Dish* dish = (Dish*)belongings;
	dish->PutDish();
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
