#include "stdafx.h"
#include "SoupBase.h"


SoupBase::SoupBase()
{
}


SoupBase::~SoupBase()
{
	DeleteGO(m_skinModelRender);
}

bool SoupBase::Start()
{

	return true;
}

//生成するスープを決める処理。
void SoupBase::DecideTheSoupType(int FoodType)
{
	if (FoodType == Belongings::enTomato){
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->Init(L"Assets/modelData/Pot/SoupBase/tomato/soupBase_tomato.cmo");
	}

	if (FoodType == Belongings::enOnion) {
		m_skinModelRender->Init(L"Assets/modelData/Pot/SoupBase/onion/soupBase_onion.cmo");
		m_skinModelRender->SetPosition(m_position);
	}

}

void SoupBase::Update()
{

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}