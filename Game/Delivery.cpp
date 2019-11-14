#include "stdafx.h"
#include "Delivery.h"


Delivery::Delivery()
{
}


Delivery::~Delivery()
{
}

bool Delivery::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Delivery/derivery.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);
	
	m_skinModelRenderCollidion = NewGO<SkinModelRender>(0, "collidion");
	m_skinModelRenderCollidion->Init(L"Assets/modelData/ColidionBox/collidionBoxLong.cmo");
	m_skinModelRenderCollidion->SetPosition(m_position);
	m_skinModelRenderCollidion->SetScale(m_scale);
	m_skinModelRenderCollidion->SetRotation(m_rotation);

	m_physicsStaticObject.CreateMeshObject(m_skinModelRenderCollidion->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollidion);

	m_physicsStaticObject.SetUserIndex(enDelivery);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}

void Delivery::Update()
{

}
