#pragma once
#include "Belongings.h"
#include "Cuisine.h"
class Dish : public Belongings
{
public:
	Dish();
	~Dish();

	bool Start();
	void Update();

	/// <summary>
	/// お皿の状態管理。
	/// </summary>
	void PutDish();

	/// <summary>
	/// 状態変化によるモデルの変更。
	/// </summary>
	void DishModelChange();

	/// <summary>
	/// お皿の状態。
	/// </summary>
	enum DishState
	{
		endefault,				//きれいなお皿。
		endirty,				//汚れてる。
		enSomethingOnBoard,		//何か乗っているとき。
	};

	/// <summary>
	/// お皿の状態をセットする処理。
	/// </summary>
	/// <param name="dishState">お皿の状態</param>
	void SetDishState(DishState dishState)
	{
		m_dishState = static_cast<DishState>(dishState);
	}

	/// <summary>
	/// お皿の状態を取得する。
	/// </summary>
	/// <returns>お皿の座標</returns>
	int GetState()
	{
		return m_dishState;
	}

private:

	DishState m_dishState = endefault;			//お皿の状態。
	DishState m_oldDishState = endefault;		//お皿の状態(1フレーム前)。

	Cuisine* m_cuisine = nullptr;				//お料理。

};

