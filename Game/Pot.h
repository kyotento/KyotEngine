/// <summary>
/// お鍋。
/// </summary>
#pragma once
#include "Belongings.h"
#include "SoupBase.h"
#include "Gauge.h"
#include "Check.h"
#include "Danger.h"
#include "Fire.h"

class Pot : public Belongings
{
public:
	Pot();
	~Pot();

	bool Start();
	void Update();

	/// <summary>
	/// 状態を変化させる。
	/// </summary>
	void StateChange();

	/// <summary>
	/// スープが投入された時の処理
	/// </summary>
	void Soup();

	/// <summary>
	/// スープを消す処理。
	/// </summary>
	void DeleteLikeSoup();

	/// <summary>
	/// 画像の座標更新関数。
	/// </summary>
	void Vector2DUpdate();

	/// <summary>
	/// 危険マーク2D描画処理。
	/// </summary>
	void Danger2D();

	/// <summary>
	/// 火事マーク2D描画処理。
	/// </summary>
	void Fire2D();

	/// <summary>
	/// お皿に入っている食べ物の種類を設定する。
	/// </summary>
	/// <param name="FoodType">お皿に入っている食べ物</param>
	void SetPutSoupFoods(int FoodType)
	{
		m_putSoupFoods = FoodType;
	}

	/// <summary>
	/// ゲージの拡大処理。
	/// ※お鍋がコンロの上にある時のみ呼ばれる。
	/// </summary>
	void PotGaugeExpansion();

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
	float m_dangerStartTimer = 0;	//危険マークが出るまでのタイマー。

	bool m_checkFlag = false;		//チェックマークが生成されているかどうか。
	bool m_dangerFlag = false;		//危険マークが生成されているかどうか。
	bool m_fireFlag = false;		//火事マークが生成されているとき。

	CVector3 m_soupPos = CVector3::Zero();			//スープの座標。
	CVector3 m_gaugePos = CVector3::Zero();			//ゲージの座標。


	SoupBase* m_soupBase = nullptr;			//スープ部分。
	Gauge* m_gauge = nullptr;				//ゲージ。
	Belongings* m_food = nullptr;			//食べ物。
	Check* m_check = nullptr;				//チェックマーク。
	Danger* m_danger = nullptr;				//危険マーク。
	Fire* m_fire = nullptr;					//火事マーク。

};
