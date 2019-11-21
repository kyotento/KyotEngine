#include "stdafx.h"
#include "DishDirty.h"


DishDirty::DishDirty()
{
	//お皿であるという設定。
	m_identification = enDish;
}


DishDirty::~DishDirty()
{
}

bool DishDirty::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Dish/DirtyDish.cmo");			//汚れたお皿。
	m_skinModelRender->SetPosition(m_position);

	return true;
}

void DishDirty::AddDish()
{
	m_dirtyDishNum += 1;
	m_dishDirtyList.emplace_back(NewGO<SkinModelRender>(0, "skinmodel"));
	m_dishDirtyList.back()->Init(L"Assets/modelData/Dish/DirtyDish.cmo");			//汚れたお皿。
	m_dishDirtyList.back()->SetPosition(m_position);
}

void DishDirty::Update()
{
	m_skinModelRender->SetPosition(m_position);
	int y = 1;
	for (auto& model : m_dishDirtyList) {
		model->SetPosition(m_position + CVector3::Up()*y*5.0f);
		y++;
	}
}
