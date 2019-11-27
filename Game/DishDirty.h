/// <summary>
/// 汚れたお皿。
/// </summary>
#pragma once
#include "Belongings.h"

class DishDirty : public Belongings
{
public:
	DishDirty();
	~DishDirty();

	bool Start();
	void Update();

	/// <summary>
	/// 乗っているお皿の数を増やす処理。
	/// </summary>
	void AddDish();

	/// <summary>
	/// 乗っているお皿の数を減らす処理。
	/// </summary>
	void DeleteDishs();

	/// <summary>
	/// 汚れたお皿の数を設定する。
	/// </summary>
	/// <param name="dirtyDishNum">汚れたお皿の数</param>
	void SetDirtyDishNum(int dirtyDishNum)
	{
		m_dirtyDishNum = dirtyDishNum;
	}

	/// <summary>
	/// 汚れたお皿の数を取得する。
	/// </summary>
	/// <returns>汚れたお皿の数</returns>
	int GetDirtyDishNum()
	{
		return m_dirtyDishNum;
	}

private:

	int m_dirtyDishNum = 0;			//汚れたお皿の数。

	typedef std::list<SkinModelRender*>DishDirtyList;			//お皿を重ねるためのリスト。
	DishDirtyList m_dishDirtyList;								//リスト。

};

