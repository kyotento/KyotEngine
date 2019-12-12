#include "stdafx.h"
#include "Cuisine.h"
#include "Belongings.h"

Cuisine::Cuisine()
{
}


Cuisine::~Cuisine()
{
}


bool Cuisine::Start()
{

	return true;
}

//スープを生成する処理。
void Cuisine::NewSoup(int FoodType)
{
	if (FoodType == Belongings::enTomato) {			//トマトだった時。
		m_skinModelRender->Init(L"Assets/modelData/Cuisine/tomato_soup.cmo");			//トマトスープを生成する。
		m_skinModelRender->SetPosition(m_position);										//座標を指定する。
	}	

	if (FoodType == Belongings::enOnion) {			//玉ねぎだった時。
		m_skinModelRender->Init(L"Assets/modelData/Cuisine/onion_soup.cmo");			//玉ねぎスープを生成する。
		m_skinModelRender->SetPosition(m_position);										//座標を指定する。
	}
}

void Cuisine::Update()
{
	m_skinModelRender->SetPosition(m_position);			//座標を更新する。

}