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

void Dish::PutDish()
{
	m_cuisine = NewGO<Cuisine>(0, "cuisine");			//料理クラスをNewする。
	m_cuisine->NewSoup();								//スープを生成する。
	m_cuisine->SetPosition(m_position);					//スープの座標を更新する。
}

void Dish::DishModelChange()
{
	if (m_oldDishState != m_dishState) {			//状態が変化したら(枚フレーム初期化すると重いから条件を追加)。

		switch (m_dishState)			//状態変化。
		{
		case endefault:

			m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//きれいなお皿。

			break;

		case enSomethingOnBoard:

			m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//きれいなお皿。

			break;

		}

	}
	m_oldDishState = m_dishState;			//代入。
}

/// <summary>
/// お皿リストにお皿を追加する。
/// </summary>
void Dish::AddDishList()
{
	m_dishListNum += 1;
	m_dishList.emplace_back(NewGO<SkinModelRender>(0, "skinmodel"));
	m_dishList.back()->Init(L"Assets/modelData/Dish/Dish.cmo");			//汚れたお皿。
	m_dishList.back()->SetPosition(m_position);
}

void Dish::Update()
{
	m_skinModelRender->SetPosition(m_position);			//座標の更新。

	DishModelChange();

	if (m_cuisine != nullptr) {					//スープが生成しているとき。
		m_cuisine->SetPosition(m_position);		//スープの座標を更新する。
	}

	int y = 1;
	for (auto& model : m_dishList) {
		model->SetPosition(m_position + CVector3::Up()*y*5.0f);
		y++;
	}

}