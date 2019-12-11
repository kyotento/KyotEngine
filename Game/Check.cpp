#include "stdafx.h"
#include "Check.h"


Check::Check()
{
}


Check::~Check()
{
	DeleteGO(m_skinModelRender);			//スキンモデルを消す。
}

bool Check::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinModel");			
	m_skinModelRender->Init(L"Assets/modelData/2D/Check/check.cmo", nullptr, 0, "PSMain", "VSMain", true, false);		//初期化。
	m_skinModelRender->SetPosition(m_position);			//座標を指定。
	m_skinModelRender->SetScale(m_scale);				//拡大率を指定。

	return true;
}

void Check::Update()
{
	m_skinModelRender->SetPosition(m_position);			//座標を更新。

}