#include "stdafx.h"
#include "Kitchen.h"


Kitchen::Kitchen()
{
}


Kitchen::~Kitchen()
{
}


bool Kitchen::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/kitchen/kitchen.cmo");
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

	m_physicsStaticObject.SetUserIndex(enKitchen);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}


void Kitchen::Update()
{


}
