#pragma once
#include "Belongings.h"
class Dish : public Belongings
{
public:
	Dish();
	~Dish();

	bool Start();
	void Update();

	/// <summary>
	/// お皿の状態を取得する。
	/// </summary>
	/// <returns>お皿の状態</returns>
	int GetState()
	{
		return m_dishState;
	}

private:

	/// <summary>
	/// お皿の状態。
	/// </summary>
	enum DishState
	{
		endefault,				//きれいなお皿。
		endirty,				//汚れてる。
		enSomethingOnBoard,		//何か乗っているとき。
	};

	DishState m_dishState = endefault;			//お皿の状態。


};

