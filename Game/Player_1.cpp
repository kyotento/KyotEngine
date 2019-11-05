#include "stdafx.h"
#include "Player_1.h"


Player_1::Player_1()
{
}


Player_1::~Player_1()
{
}

bool Player_1::Start()
{
	//ƒ‚ƒfƒ‹‚Ì‰Šú‰»B
	m_skinModelRender->Init(L"Assets/modelData/Chef/chef_1.cmo",m_animationClips,enanimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->PlayAnimation(enanimationClip_Idle);
	return true;
}

void Player_1::Update()
{
	Movement(m_controllerNumber);
	Rotation();
	ForwardDirectionRay(m_controllerNumber);
	ActionProcessing(m_controllerNumber);

}
