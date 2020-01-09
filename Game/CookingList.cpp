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
//	m_dishName = enTomatoSoup;

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
		m_foodtype = 1;				//料理に必要な食べ物の種類。
	}
}

int CookingList::OrderSetting()
{
	//todo　実際はステージごとに料理を変える。
	//ステージ１。
	float a = random().GetRandDouble();		//０～１のランダムな値をaに代入。

	if (a <= 0.500f) {						//0.5以下の場合。
		m_dishName = enTomatoSoup;			//料理をトマトスープに。
	}
	else{									//0.5より大きいとき。
		m_dishName = enOnionSoup;			//料理を玉ねぎスープに。
	}

	return m_dishName;			//料理名を返す。
}

void CookingList::Update()
{
	CookingInformations();
}