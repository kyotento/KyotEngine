#include "stdafx.h"
#include "Pot.h"


Pot::Pot()
{
}


Pot::~Pot()
{
	DeleteGO(m_skinModelRender);
}


bool Pot::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Pot/Pot.cmo");
	m_skinModelRender->SetPosition(m_position);


	return true;
}

void Pot::Kari()
{
	m_soupBase = NewGO<SoupBase>(0, "soup");
	m_soupBase->SetPosition(m_position);

}


void Pot::Update()
{
	m_skinModelRender->SetPosition(m_position);
}