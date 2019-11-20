#include "stdafx.h"
#include "DishHold.h"
#include "Delivery.h"

DishHold::DishHold()
{
}


DishHold::~DishHold()
{
}

bool DishHold::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/DishHold/DishHold.cmo");
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

	m_physicsStaticObject.SetUserIndex(enDishHold);
	m_physicsStaticObject.SetUserPointer(this);

	m_dishPosition.x = m_position.x;
	m_dishPosition.z = m_position.z;
	m_dishPosition.y = m_position.y += 70.f;

	return true;
}

void DishHold::NumberOfDished()
{
	if (m_oldDishNum < m_dishNum) {		//お皿の数が増えた時。

		for (int i = 0; i < m_dishNum; i++)		//お皿の数だけ強くなれるよ。（曲::TOMORROW）。
		{
			m_dishPosition.y += 3.f;
		}

		m_dish = NewGO<Dish>(0, "dish");		//お皿の生成。
		m_dish->SetPosition(m_dishPosition);

	}
	m_oldDishNum = m_dishNum;			//お皿の数が変更されたかを確認するために代入。
}

void DishHold::Update()
{
	NumberOfDished();			//お皿の数を管理するクラス。

}
