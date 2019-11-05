#include "stdafx.h"
#include "Player_2.h"


Player_2::Player_2()
{
}


Player_2::~Player_2()
{
}


bool Player_2::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Chef/chef_2.cmo", m_animationClips, enanimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->PlayAnimation(enanimationClip_Idle);
	
	return true;
}


void Player_2::Update()
{
	Movement(m_controllerNumber);
	Rotation();
	ForwardDirectionRay(m_controllerNumber);
	ActionProcessing(m_controllerNumber);
}