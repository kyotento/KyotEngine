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
	/// スープが投入されたときの処理。
	/// </summary>
	void Soup();

	/// <summary>
	/// スープを消す処理。
	/// </summary>
	void DeleteLikeSoup();

private:

	CVector3 m_soupPos = CVector3::Zero();			//スープの座標。
	CVector3 m_gaugePos = CVector3::Zero();			//ゲージの座標。


	SoupBase* m_soupBase = nullptr;			//スープ部分。
	Gauge* m_gauge = nullptr;				//ゲージ。

};
