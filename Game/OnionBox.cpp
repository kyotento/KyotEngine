#include "stdafx.h"
#include "OnionBox.h"


OnionBox::OnionBox()
{
}


OnionBox::~OnionBox()
{
}

bool OnionBox::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/FoodBox/Onion/OnionBox.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	m_physicsStaticObject.CreateMeshObject(m_skinModelRenderCollidion->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollidion);

	m_physicsStaticObject.SetUserIndex(enOnionBox);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}

Onion* OnionBox::NewFood(int a)
{
	m_onion = NewGO<Onion>(0, "onion");
	QueryGOs<Player>("player", [&](Player* player)->bool
		{
			m_onion->SetPosition(player->GetPosition());

			return false;
		});
	return m_onion;
}

void OnionBox::Update()
{

}