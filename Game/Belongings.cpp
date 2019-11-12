#include "stdafx.h"
#include "Belongings.h"
#include "Pot.h" 

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
void Belongings::SetSoupBase(Belongings* bel)
{
	Pot* pot = (Pot*)bel;		//どのPotか検索をかける。	
	pot->Soup();				//スープの素を生成する。	
}

void Belongings::Update()
{

}
