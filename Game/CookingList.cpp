#include "stdafx.h"
#include "CookingList.h"


CookingList::CookingList()
{
}


CookingList::~CookingList()
{
}

bool CookingList::Start()
{
	//todo 仮。
	m_dishName = enTomatoSoup;

	return true;
}

void CookingList::CookingInformations()
{
	if (m_dishName == enTomatoSoup)		//トマトスープのとき。
	{
		m_materialNum = 3;			//料理に必要な食べ物の数。
		m_foodtype = 1;				//料理に必要な食べ物の種類。
	}

	if (m_dishName == enOnionSoup)		//玉ねぎスープのとき。
	{
		m_materialNum = 3;			//料理に必要な食べ物の数。
		m_materialNum = 1;			//料理に必要な食べ物の種類。
	}
}

void CookingList::Update()
{
	CookingInformations();
}