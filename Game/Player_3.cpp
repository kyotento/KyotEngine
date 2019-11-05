#include "stdafx.h"
#include "Player_3.h"


Player_3::Player_3()
{
}


Player_3::~Player_3()
{
}

bool Player_3::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/chef_3.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	return true;
}

void Player_3::Update()
{

	Movement(2);
	Rotation();

}
