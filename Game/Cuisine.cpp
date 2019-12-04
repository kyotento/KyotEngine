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

void Cuisine::NewSoup(int FoodType)
{
	if (FoodType == Belongings::enTomato) {
		m_skinModelRender->Init(L"Assets/modelData/Cuisine/tomato_soup.cmo");
		m_skinModelRender->SetPosition(m_position);
	}

	if (FoodType == Belongings::enOnion) {
		m_skinModelRender->Init(L"Assets/modelData/Cuisine/onion_soup.cmo");
		m_skinModelRender->SetPosition(m_position);
	}
}

void Cuisine::Update()
{
	m_skinModelRender->SetPosition(m_position);

}