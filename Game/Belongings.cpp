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
void Belongings::SetSoupBase(Belongings* puttingBelongings)
{
	Pot* pot = (Pot*)puttingBelongings;		//�ǂ�Pot��������������B	
	pot->Soup();				//�X�[�v�̑f�𐶐�����B	
}

//�X�[�v�����������B
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

//���M�ɐH�ו���u�������B
void Belongings::PutDishs(Belongings* belongings ,int FoodType)
{
	Dish* dish = (Dish*)belongings;
	dish->PutDish(FoodType);
}

// ���M�􂢏�̏d�˂Ă��邨�M���炨�M����Ƃ鏈���B
void Belongings::PutDishFromKitchen(Belongings* belongings, Kitchen* kitchen)
{
	Dish* dish = (Dish*)belongings;
	dish->DeleteDishList(kitchen);
}

void Belongings::Update()
{

}
