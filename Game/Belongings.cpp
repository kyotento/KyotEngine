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

//todo ���̂��������Ă��镨���Ƃɐ���������̂�ς���B(SoupBase�N���X���ł�����ق���������������Ȃ��B)
void Belongings::SetSoupBase(Belongings* belongings)
{
	Pot* pot = (Pot*)belongings;		//�ǂ�Pot��������������B	
	pot->Soup();				//�X�[�v�̑f�𐶐�����B	
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
