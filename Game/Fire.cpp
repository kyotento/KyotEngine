#include "stdafx.h"
#include "Fire.h"


Fire::Fire()
{
}


Fire::~Fire()
{
	DeleteGO(m_skinModelRender);
}

bool Fire::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinModel");
	m_skinModelRender->Init(L"Assets/modelData/2D/Fire/fire.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
	m_skinModelRender->SetPosition(m_position);

	return true;
}

void Fire::Update()
{
	m_skinModelRender->SetPosition(m_position);
}