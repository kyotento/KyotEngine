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
	/// ‚¨M’u‚«‚ÌƒCƒ“ƒXƒ^ƒ“ƒX‚ğæ“¾‚·‚éB
	/// </summary>
	/// <param name="dishHold">‚¨M’u‚«</param>
	void SetDishHold(DishHold* dishHold)
	{
		m_dishHold = dishHold;
	}

	///// <summary>
	///// ‰^‚Î‚ê‚Ä‚«‚½‚¨M‚Ìó‘Ô‚ğİ’è‚·‚éB
	///// </summary>
	///// <param name="deliveryDishCuisine">‰^‚Î‚ê‚Ä‚«‚½‚¨M‚Ìó‘Ô‚ğ‚ğŠi”[‚·‚é</param>
	//void SetDeliveryDishCuisine(int deliveryDishCuisine)
	//{
	//	m_deliveryDishCuisine = deliveryDishCuisine;
	//}

	///// <summary>
	///// ‰^‚Î‚ê‚Ä‚«‚½‚¨M‚Ìó‘Ô‚ğæ“¾‚·‚éB
	///// </summary>
	///// <returns></returns>
	//int GetDeliveryDishCuisine()
	//{
	//	return m_deliveryDishCuisine;
	//}

private:

	int m_DishNum3 = 0;			//”[•i‚³‚ê‚½‚¨M‚Ì”B

	float m_StateChangeTime = 0.f;

	bool m_TimeAdvanced = false;

	DishHold* m_dishHold = nullptr;

};

