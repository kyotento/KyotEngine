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
	m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//初期化。
	m_skinModelRender->SetPosition(m_position);							//座標を指定。
	m_skinModelRender->SetRotation(m_rotation);							//回転を指定。

	return true;
}

//料理の管理。
void Dish::PutDish()
{
	m_cuisine = NewGO<Cuisine>(0, "cuisine");			//料理クラスをNewする。
	m_cuisine->NewSoup();								//スープを生成する。
	m_cuisine->SetPosition(m_position);					//スープの座標を更新する。
}

//状態変化によるモデルの変更。
void Dish::DishModelChange()
{
	if (m_oldDishState != m_dishState) {			//状態が変化したら(枚フレーム初期化すると重いから条件を追加)。

		switch (m_dishState)			//状態変化。
		{
		case endefault:			//きれいなお皿のとき。

			m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//きれいなお皿。

			break;

		case enSomethingOnBoard:		//お皿に何か(料理)が乗っているとき。

			m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//きれいなお皿。

			break;

		}
	}

	m_oldDishState = m_dishState;			//代入。
}

//お皿リストにお皿を追加する。
void Dish::AddDishList()
{
	m_dishListNum += 1;				//お皿の数を増やす。
	m_dishList.emplace_back(NewGO<SkinModelRender>(0, "skinmodel"));		//新しくお皿を生成する。
	m_dishList.back()->Init(L"Assets/modelData/Dish/Dish.cmo");				//お皿。
	m_dishList.back()->SetPosition(m_position);								//座標を指定。
}

void Dish::DeleteDishList()
{
	m_dishListNum -= 1;					//お皿の数を減らす。
	DeleteGO(m_dishList.back());		//一番最後に生成したお皿を消す。
	m_dishList.pop_back();				//一番最後のリストの要素が消える。
}

void Dish::Update()
{
	m_skinModelRender->SetPosition(m_position);			//座標の更新。

	DishModelChange();			//状態変化によるモデルの変更。

	if (m_cuisine != nullptr) {					//スープが生成しているとき。
		m_cuisine->SetPosition(m_position);		//スープの座標を更新する。
	}

	int y = 1;
	for (auto& model : m_dishList) {			//リストの数分ループする。　
		model->SetPosition(m_position + CVector3::Up()*y*7.0f);		//Y座標を少し上げてやる。　	
		y++;		//Yを更新。
	}

}