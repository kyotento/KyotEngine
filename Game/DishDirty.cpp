#include "stdafx.h"
#include "DishDirty.h"


DishDirty::DishDirty()
{
	//���M�ł���Ƃ����ݒ�B
	m_identification = enDirtyDish;
}


DishDirty::~DishDirty()
{
}

bool DishDirty::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Dish/DirtyDish.cmo");			//���ꂽ���M�B
	m_skinModelRender->SetPosition(m_position);
	m_dirtyDishNum += 1;

	return true;
}

void DishDirty::AddDish()
{
	m_dirtyDishNum += 1;
	m_dishDirtyList.emplace_back(NewGO<SkinModelRender>(0, "skinmodel"));
	m_dishDirtyList.back()->Init(L"Assets/modelData/Dish/DirtyDish.cmo");			//���ꂽ���M�B
	m_dishDirtyList.back()->SetPosition(m_position);
}

void DishDirty::DeleteDishs()
{
	DeleteGauge();
	DeleteGO(m_dishDirtyList.back());		//��ԍŌ�ɐ����������M�������B
	m_dishDirtyList.pop_back();				//��ԍŌ�̃��X�g�̗v�f��������B
	m_dirtyDishNum -= 1;					//���M�̐������炷�B
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
