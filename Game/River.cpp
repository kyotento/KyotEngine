#include "stdafx.h"
#include "River.h"


River::River()
{
}


River::~River()
{
	DeleteGO(m_skinModelRender);
}

bool River::Start()
{
	//モデルの生成処理諸々。
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/river.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}


void River::Update()
{
	m_skinModelRender->UVScroll(-1.f, 1.f, 5.f);		//UVスクロール。
}