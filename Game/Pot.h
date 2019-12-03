/// <summary>
/// お鍋。
/// </summary>
#pragma once
#include "Belongings.h"
#include "SoupBase.h"
#include "Gauge.h"

class Pot : public Belongings
{
public:
	Pot();
	~Pot();

	bool Start();
	void Update();

	/// <summary>
	/// スープが投入された時の処理
	/// </summary>
	void Soup();

	/// <summary>
	/// スープを消す処理。
	/// </summary>
	void DeleteLikeSoup();

	/// <summary>
	/// お皿に入っている食べ物の種類を設定する。
	/// </summary>
	/// <param name="FoodType"></param>
	void SetPutSoupFoods(int FoodType)
	{
		m_putSoupFoods = FoodType;
	}

	/// <summary>
	/// お鍋に入っている食べ物の種類を検索する。
	/// </summary>
	/// <returns>お鍋に入っている食べ物の種類</returns>
	int GetPutSoupFoods()
	{
		return m_putSoupFoods;
	}

private:

	int m_putSoupFoods = 0;			//お鍋に入っている食べ物の種類。

	CVector3 m_soupPos = CVector3::Zero();			//スープの座標。
	CVector3 m_gaugePos = CVector3::Zero();			//ゲージの座標。


	SoupBase* m_soupBase = nullptr;			//スープ部分。
	Gauge* m_gauge = nullptr;				//ゲージ。
	Belongings* m_food = nullptr;			//食べ物。

};
