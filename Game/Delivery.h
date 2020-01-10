#pragma once
#include "ObjectAbove.h"
#include "DishHold.h"

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

	///// <summary>
	///// 運ばれてきたお皿の状態を設定する。
	///// </summary>
	///// <param name="deliveryDishCuisine">運ばれてきたお皿の状態をを格納する</param>
	//void SetDeliveryDishCuisine(int deliveryDishCuisine)
	//{
	//	m_deliveryDishCuisine = deliveryDishCuisine;
	//}

	///// <summary>
	///// 運ばれてきたお皿の状態を取得する。
	///// </summary>
	///// <returns></returns>
	//int GetDeliveryDishCuisine()
	//{
	//	return m_deliveryDishCuisine;
	//}

private:

	int m_DishNum3 = 0;			//納品されたお皿の数。

	float m_StateChangeTime = 0.f;

	bool m_TimeAdvanced = false;

	DishHold* m_dishHold = nullptr;

};

