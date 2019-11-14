#include "stdafx.h"
#include "Dish.h"


Dish::Dish()
{
	//お皿であるという設定。
	m_identification = enDish;
}


Dish::~Dish()
{
}

bool Dish::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}

void Dish::Update()
{
	m_skinModelRender->SetPosition(m_position);			//座標の更新。

}