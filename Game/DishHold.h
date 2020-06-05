/// <summary>
/// 客が食器を返してくるところ。(汚れたお皿置き場)。
/// </summary>
#pragma once
#include "ObjectAbove.h"
#include "Dish.h"
#include "DishDirty.h"

class DishHold : public ObjectAbove
{

public:
	DishHold();
	~DishHold();

	bool Start();
	void Update();

	/// <summary>
	///　乗っているお皿の数を管理する関数。
	/// </summary>
	void NumberOfDished();

	/// <summary>
	/// お皿の数を設定する。
	/// </summary>
	/// <param name="dishNum">お皿の数</param>
	void SetDishNum(int dishNum)
	{
		m_dishNum = dishNum;
	}

	/// <summary>
	/// お皿の数を取得する。
	/// </summary>
	/// <returns>お皿の数</returns>
	int GetDishNum()
	{
		return m_dishNum;
	}

	/// <summary>
	/// 汚れたお皿のインスタンスを取得する。
	/// </summary>
	/// <returns>汚れたお皿のインスタンス</returns>
	DishDirty *GetDirtyDishInstance()
	{
		return m_dishDirty;
	}

private:

	int m_dishNum = 0;			//乗っているお皿の数。
	int m_oldDishNum = 0;		//１フレーム前に載っていたお皿の数。

	CVector3 m_dishPosition = CVector3::Zero();		//お皿の座標。

	Dish* m_dish = nullptr;							//お皿。
	DishDirty* m_dishDirty = nullptr;				//汚れたお皿。

};

