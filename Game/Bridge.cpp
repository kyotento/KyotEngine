#include "stdafx.h"
#include "Bridge.h"


Bridge::Bridge()
{
}


Bridge::~Bridge()
{
	DeleteGO(m_skinModelRender);
}


bool Bridge::Start()
{
	//ƒ‚ƒfƒ‹‚Ì¶¬ˆ—”XB
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/bridge/beidge.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	m_skinModelRenderCollidion = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRenderCollidion->Init(L"Assets/modelData/bridge/CollidionBridge.cmo");
	m_skinModelRenderCollidion->SetPosition(m_position);
	m_skinModelRenderCollidion->SetScale(m_scale);
	m_skinModelRenderCollidion->SetRotation(m_rotation);

	m_physicsStaticObject.CreateMeshObject(m_skinModelRenderCollidion->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollidion);
	return true;
}

void Bridge::Update()
{

}