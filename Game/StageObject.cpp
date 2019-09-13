#include "stdafx.h"
#include "StageObject.h"


StageObject::StageObject()
{
}


StageObject::~StageObject()
{

	DeleteGO(m_skinModelRender);
}


bool StageObject::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);


	return true;
}


void StageObject::Update()
{


}