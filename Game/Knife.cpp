#include "stdafx.h"
#include "Knife.h"


Knife::Knife()
{
}


Knife::~Knife()
{
	DeleteGO(m_skinModelRender);
}


bool Knife::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Knife/Knife.cmo");
	m_skinModelRender->InitSpecMap(L"Assets/sprite/knife_spec.dds");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);
//	m_skinModelRender->SetSpecPower(2.f);

	return true;
}

void Knife::Update()
{
	m_skinModelRender->SetPosition(m_position);		//座標を更新。
	m_skinModelRender->SetRotation(m_rotation);		//回転を更新。
}