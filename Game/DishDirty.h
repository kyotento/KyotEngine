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

private:

	int m_dirtyDishNum = 1;			//汚れたお皿の数。

	typedef std::list<SkinModelRender*>DishDirtyList;
	DishDirtyList m_dishDirtyList;

};

