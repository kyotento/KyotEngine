#include "stdafx.h"
#include "Cuisine.h"


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

void Cuisine::NewSoup()
{
	m_skinModelRender->Init(L"Assets/modelData/Cuisine/tomato_soup.cmo");
	m_skinModelRender->SetPosition(m_position);

}

void Cuisine::Update()
{
	m_skinModelRender->SetPosition(m_position);

}