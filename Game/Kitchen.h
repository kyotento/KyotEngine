#pragma once
#include "ObjectAbove.h"
#include "DishDirty.h"
#include "Dish.h"

class Kitchen : public ObjectAbove
{
public:
	Kitchen();
	~Kitchen();

	bool Start();
	void Update();

	/// <summary>
	/// お皿を洗う関数。
	/// </summary>
	void DishWashing();

	/// <summary>
	/// お皿のインスタンスを消去する。
	/// </summary>
	void DeleteDishInstance();

	/// <summary>
	/// 外部から汚れたお皿のインスタンスを設定する関数。
	/// </summary>
	/// <param name="dishDirty">お皿のインスタンス</param>
	void SetDishDirtyInstance(DishDirty* dishDirty)
	{
		m_dishDirty = dishDirty;
	}

	/// <summary>
	/// 汚れたお皿のインスタンスを取得する。
	/// </summary>
	/// <returns>汚れたお皿のインスタンス</returns>
	DishDirty* GetDishDirtyInstance()
	{
		return m_dishDirty;
	}

private:

	int m_timerK = 0;				//カリカリの仮。

	Dish* m_dish = nullptr;						//お皿。
	DishDirty* m_dishDirty = nullptr;			//汚れたお皿。

};

