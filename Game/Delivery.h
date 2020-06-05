/// <summary>
/// 料理を提供するところ。
/// </summary>
#pragma once
#include "ObjectAbove.h"
#include "DishHold.h"
#include "OrderGenerations.h"

class Delivery : public ObjectAbove
{
public:
	Delivery();
	~Delivery();

	bool Start();
	void Update();

	int GetDishNum()
	{
		return m_DishNum3;
	}

	/// <summary>
	/// お皿置きのインスタンスを取得する。
	/// </summary>
	/// <param name="dishHold">お皿置き</param>
	void SetDishHold(DishHold* dishHold)
	{
		m_dishHold = dishHold;
	}


private:

	int m_DishNum3 = 0;			//納品されたお皿の数。

	float m_StateChangeTime = 0.f;

	bool m_TimeAdvanced = false;
	bool GetDishTimingFlag = false;				//お皿の状態を受け取るタイミングを指定。

	DishHold* m_dishHold = nullptr;

};

