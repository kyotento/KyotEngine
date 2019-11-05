#include "stdafx.h"
#include "Knife.h"


Knife::Knife()
{
}


Knife::~Knife()
{
}


bool Knife::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Knife/Knife.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}

void Knife::Update()
{

	m_skinModelRender->SetPosition(m_position);
}