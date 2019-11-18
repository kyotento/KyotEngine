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
	pot->Soup();				//スープの素を生成する。	
}

void Belongings::DeleteSoup(Belongings* belongings)
{
	Pot* pot = (Pot*)belongings;
	pot->DeleteLikeSoup();
}

void Belongings::PutDishs(Belongings* belongings)
{
	Dish* dish = (Dish*)belongings;
	dish->PutDish();
}

void Belongings::Update()
{

}
