#include "stdafx.h"
#include "Player_4.h"


Player_4::Player_4()
{
}


Player_4::~Player_4()
{
}

bool Player_4::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/chef_4.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	return true;
}

void Player_4::Update()
{

	Movement(3);
	Rotation();
}