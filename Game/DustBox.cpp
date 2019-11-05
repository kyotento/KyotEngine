#include "stdafx.h"
#include "DustBox.h"


DustBox::DustBox()
{
}


DustBox::~DustBox()
{

}

bool DustBox::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/DustBox/DustBox.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_skinModelRenderCollidion = NewGO<SkinModelRender>(0, "collidion");
	m_skinModelRenderCollidion->Init(L"Assets/modelData/ColidionBox/collidionBox.cmo");
	m_skinModelRenderCollidion->SetPosition(m_position);
	m_skinModelRenderCollidion->SetScale(m_scale);
	m_skinModelRenderCollidion->SetRotation(m_rotation);

	m_physicsStaticObject.CreateMeshObject(m_skinModelRenderCollidion->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollidion);

	m_physicsStaticObject.SetUserIndex(4);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}

void DustBox::Update()
{

}