#include "stdafx.h"
#include "Onion.h"


Onion::Onion()
{
}


Onion::~Onion()
{
	DeleteGO(m_skinModelRender);
}


bool Onion::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Food/Onion/onion.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);


	return true;
}

void Onion::Update()
{
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);

}