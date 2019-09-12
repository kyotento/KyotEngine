#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

bool Player::Start()
{
	//モデルの初期化。
	m_skinModelRender = NewGO<SkinModelRender>(0, "player");
	m_skinModelRender->Init(L"Assets/modelData/chef_1.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);

	//キャラコンの初期化。
	m_characon.Init(10.f, 50.f, m_characonPos);

	return true;
}

void Player::Update()
{
	Movement();
	Rotation(); 

}

void Player::Movement()
{

	CVector3 stickPower;		//左スティックの傾き具合を保持するためのもの。

	stickPower.x = g_pad[0].GetLStickXF();
	stickPower.y = 0.f;
	stickPower.z = g_pad[0].GetLStickYF();

	m_move = stickPower * m_moveSpeed;
	m_position = m_characon.Execute(1.0, m_move);

	m_skinModelRender->SetPosition(m_position);
}

void Player::Rotation()
{

}