#include "stdafx.h"
#include "DishDirty.h"


DishDirty::DishDirty()
{
	//‚¨ŽM‚Å‚ ‚é‚Æ‚¢‚¤Ý’èB
	m_identification = enDirtyDish;
}


DishDirty::~DishDirty()
{
}

bool DishDirty::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Dish/DirtyDish.cmo");			//‰˜‚ê‚½‚¨ŽMB
	m_skinModelRender->SetPosition(m_position);
	m_dirtyDishNum += 1;

	return true;
}

void DishDirty::AddDish()
{
	m_dirtyDishNum += 1;
	m_dishDirtyList.emplace_back(NewGO<SkinModelRender>(0, "skinmodel"));
	m_dishDirtyList.back()->Init(L"Assets/modelData/Dish/DirtyDish.cmo");			//‰˜‚ê‚½‚¨ŽMB
	m_dishDirtyList.back()->SetPosition(m_position);
}

void DishDirty::DeleteDishs()
{
	DeleteGauge();
	DeleteGO(m_dishDirtyList.back());		//ˆê”ÔÅŒã‚É¶¬‚µ‚½‚¨ŽM‚ðÁ‚·B
	m_dishDirtyList.pop_back();				//ˆê”ÔÅŒã‚ÌƒŠƒXƒg‚Ì—v‘f‚ªÁ‚¦‚éB
	m_dirtyDishNum -= 1;					//‚¨ŽM‚Ì”‚ðŒ¸‚ç‚·B
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
