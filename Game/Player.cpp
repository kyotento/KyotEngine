#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{

	m_skinModelRender = NewGO<SkinModelRender>(0, "player");
	m_skinModelRender->Init(L"Assets/modelData/chef_1.cmo");
	m_skinModelRender->SetPosition(m_position);

	return true;
}

void Player::Update()
{

}
