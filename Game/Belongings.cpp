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

//todo ���̂��������Ă��镨���Ƃɐ���������̂�ς���B(SoupBase�N���X���ł�����ق���������������Ȃ��B)
void Belongings::SetSoupBase(Belongings* belongings)
{
	Pot* pot = (Pot*)belongings;		//�ǂ�Pot��������������B	
	pot->Soup();				//�X�[�v�̑f�𐶐�����B	
}

void Belongings::Update()
{

}
