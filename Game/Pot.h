/// <summary>
/// お鍋。
/// </summary>
#pragma once
#include "KitchenWare.h"
#include "SoupBase.h"

class Pot : public KitchenWare
{
public:
	Pot();
	~Pot();

	bool Start();
	void Update();

	/// <summary>
	/// スープの部分の処理。
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
		enComplete		//料理完成。
	};


	CVector3 m_soupPos;			//スープの座標。

	PotState m_potState = enZero;			//鍋の状態を格納したもの。

	SoupBase* m_soupBase = nullptr;			//スープ部分。

};
