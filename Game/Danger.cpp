#include "stdafx.h"
#include "Danger.h"

Danger::Danger()
{
}


Danger::~Danger()
{
	DeleteGO(m_skinModelRender);
}


bool Danger::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinModel");
	m_skinModelRender->Init(L"Assets/modelData/2D/Danger/danger.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);

	return true;
}

void Danger::Update()
{



	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);

}