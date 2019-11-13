/// <summary>
/// お鍋。
/// </summary>
#pragma once
#include "KitchenWare.h"
#include "SoupBase.h"
#include "Gauge.h"

class Pot : public KitchenWare
{
public:
	Pot();
	~Pot();

	bool Start();
	void Update();

	/// <summary>
	/// スープが投入されたときの処理。
	/// </summary>
	void Soup();

private:

	/// <summary>
	/// 鍋の状態。
	/// </summary>
	enum PotState
	{
		enZero,			//何も入っていない。
		enOne,			//一つ何かが入っている。
		enTwo,			//ふたつなにかがはいっている。
		enThree,		//三つ何かが入っている状態。
		enComplete		//料理完成。湯で終わっている。
	};


	CVector3 m_soupPos = CVector3::Zero();			//スープの座標。
	CVector3 m_gaugePos = CVector3::Zero();			//ゲージの座標。

	PotState m_potState = enZero;			//鍋の状態を格納したもの。

	SoupBase* m_soupBase = nullptr;			//スープ部分。
	Gauge* m_gauge = nullptr;				//ゲージ。

};
