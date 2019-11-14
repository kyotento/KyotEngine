#include "stdafx.h"
#include "CuttingDesk.h"


CuttingDesk::CuttingDesk()
{
}


CuttingDesk::~CuttingDesk()
{
}

bool CuttingDesk::Start()
{

	m_skinModelRender->Init(L"Assets/modelData/cutting_board/cutting_desk.cmo");
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

	m_physicsStaticObject.SetUserIndex(enCuttingDesk);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}

void CuttingDesk::Update()
{

}