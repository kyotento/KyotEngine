/// <summary>
/// 料理の名前のクラス。
/// </summary>
#pragma once
#include "GameObject.h"
#include "Belongings.h"
#include "Random.h"

class CookingList : public GameObject
{
public:
	CookingList();
	~CookingList();

	bool Start();
	void Update();

	/// <summary>
	/// 料理の情報を格納してある。
	/// </summary>
	void CookingInformations();

	/// <summary>
	/// 料理を設定する。
	/// </summary>
	int OrderSetting();

	/// <summary>
	/// 料理の名前リスト。
	/// </summary>
	enum cookingList
	{
		enTomatoSoup,		//トマトスープ。
		enOnionSoup,		//玉ねぎスープ。
		encookingListNum	//料理名数。
	};

	/// <summary>
	/// 作成する料理の名前を取得する。
	/// </summary>
	/// <returns>料理名</returns>
	cookingList GetCookingList()
	{
		return m_dishName;
	}

	/// <summary>
	/// 料理に必要な材料の種類の数。
	/// </summary>
	/// <returns>料理に必要な材料の種類</returns>
	int GetFoodType()
	{
		return m_foodtype;
	}

	/// <summary>
	/// 料理に必要な材料の数を取得する。
	/// </summary>
	/// <returns>料理に必要な材料の数</returns>
	int GetMaterialNum()
	{
		return m_materialNum;
	}

private:

	int m_materialNum = 0;		//料理に必要な材料の数。
	int m_foodtype = 0;			//料理に必要な材料の種類。

	cookingList m_dishName = encookingListNum;		//料理名。

};

