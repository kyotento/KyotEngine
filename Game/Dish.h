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
	void SetState(DishState dishState)
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


};

