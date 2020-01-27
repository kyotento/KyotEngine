#include "stdafx.h"
#include "Flag.h"


Flag::Flag()
{
}


Flag::~Flag()
{
	DeleteGO(m_skinModelRender);
}

bool Flag::Start()
{
	//ƒ‚ƒfƒ‹‚Ì¶¬”XB
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/Flag/Flag.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}

void Flag::Update()
{

}