#include "stdafx.h"
#include "StageSelectFloor.h"


StageSelectFloor::StageSelectFloor()
{
}


StageSelectFloor::~StageSelectFloor()
{
}


bool StageSelectFloor::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodelrender");
	m_skinModelRender->Init(L"Assets/modelData/floor.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);
	m_physicsStaticObject.CreateMeshObject(m_skinModelRender->GetSkinModel(), m_position, m_rotation);
}

void StageSelectFloor::Update()
{

}