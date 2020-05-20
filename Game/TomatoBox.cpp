#include "stdafx.h"
#include "TomatoBox.h"


TomatoBox::TomatoBox()
{
}



TomatoBox::~TomatoBox()
{
	if (m_skinModelRender != nullptr) {
		DeleteGO(m_skinModelRender);
	}
	DeleteGOs("tomato");
}

bool TomatoBox::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/FoodBox/Tomato/TomatoBox.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	m_physicsStaticObject.CreateMeshObject(m_skinModelRenderCollidion->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollidion);

	m_physicsStaticObject.SetUserIndex(enTomatoBox);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}

Tomato* TomatoBox::NewFood(int a)
{
	m_tomato = NewGO<Tomato>(0, "tomato");

	QueryGOs<Player>("player", [&](Player* player)->bool 
	{
		m_tomato->SetPosition(player->GetPosition());

		return false;
	});

	return m_tomato;

}

void TomatoBox::Update()
{

}