#include "stdafx.h"
#include "Desk.h"


Desk::Desk()
{
}


Desk::~Desk()
{
	
}

bool Desk::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Desk/Desk.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	m_skinModelRenderCollidion = NewGO<SkinModelRender>(0, "collidion");
	m_skinModelRenderCollidion->Init(L"Assets/modelData/ColidionBox/collidionBox.cmo");
	m_skinModelRenderCollidion->SetPosition(m_position);
	m_skinModelRenderCollidion->SetScale(m_scale);
	m_skinModelRenderCollidion->SetRotation(m_rotation);

	m_physicsStaticObject.CreateMeshObject(m_skinModelRenderCollidion->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollidion);

	m_physicsStaticObject.SetUserIndex(1);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}

void Desk::Update()
{

	switch (m_state)
	{

	en_default:

		break;

	en_onObject:

		break;

	}
}
