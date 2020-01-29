#include "stdafx.h"
#include "Bus.h"

namespace {
	float a = 0;
}

Bus::Bus()
{
}


Bus::~Bus()
{
	DeleteGO(m_skinModelRender);
}


bool Bus::Start()
{
	//バスのモデル生成諸々。
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/bus/bus.cmo");
	m_skinModelRender->InitNormalMap(L"Assets/sprite/bus_normal_Normal.dds");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}

void Bus::Update()
{
	a += gametime().GetFrameDeltaTime();
	m_rotation.SetRotation(CVector3::AxisY(), a);			//回転を計算。
	m_skinModelRender->SetRotation(m_rotation);
}