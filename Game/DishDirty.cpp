#include "stdafx.h"
#include "DishDirty.h"


DishDirty::DishDirty()
{
	//お皿であるという設定。
	m_identification = enDirtyDish;
}


DishDirty::~DishDirty()
{
}

bool DishDirty::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Dish/DirtyDish.cmo");			//汚れたお皿。
	m_skinModelRender->SetPosition(m_position);
	m_dirtyDishNum += 1;

	return true;
}

void DishDirty::AddDish()
{
	m_dirtyDishNum += 1;
	m_dishDirtyList.emplace_back(NewGO<SkinModelRender>(0, "skinmodel"));
	m_dishDirtyList.back()->Init(L"Assets/modelData/Dish/DirtyDish.cmo");			//汚れたお皿。
	m_dishDirtyList.back()->SetPosition(m_position);
}

void DishDirty::DeleteDishs()
{
	DeleteGO(m_dishDirtyList.back());		//一番最後に生成したお皿を消す。
	m_dishDirtyList.pop_back();				//一番最後のリストの要素が消える。
	m_dirtyDishNum -= 1;					//お皿の数を減らす。
}

void DishDirty::GaugeUpdate()
{
	GaugeGeneration(false, 1.9f, 0.f, false);
}

void DishDirty::Update()
{
	m_skinModelRender->SetPosition(m_position);
	int y = 1;
	for (auto& model : m_dishDirtyList) {
		model->SetPosition(m_position + CVector3::Up()*y*7.0f);
		y++;
	}

}
