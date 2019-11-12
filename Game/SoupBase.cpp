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
	m_skinModelRender->Init(L"Assets/modelData/Pot/SoupBase/tomato/soupBase_tomato.cmo");
	m_skinModelRender->SetPosition(m_position);

	return true;
}

void SoupBase::Update()
{
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);

}