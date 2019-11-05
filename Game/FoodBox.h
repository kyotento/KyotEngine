#pragma once
#include "Tomato.h"
#include "Onion.h"
#include "Belongings.h"
#include "ObjectAbove.h"
/// <summary>
/// 食べ物入れの基底クラス。
/// </summary>
class Tomato;
class Onion;
class Belongings;
class FoodBox : public ObjectAbove
{
public:
	FoodBox();
	~FoodBox();

	bool Start();
	void Update();

	/// <summary>
	/// 食べ物を生成。
	/// </summary>
	void NewFood();

	/// <summary>
	/// 座標を指定。
	/// </summary>
	/// <param name="a">座標</param>
	void SetPositon(CVector3 a)
	{
		m_position = a;
	}


protected:

	Tomato* m_tomato = nullptr;
	Onion* m_onion = nullptr;
	Belongings* m_food = nullptr;

private:



};

