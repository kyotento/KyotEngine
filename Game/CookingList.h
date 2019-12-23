/// <summary>
/// 料理の名前のクラス。
/// </summary>
#pragma once
#include "GameObject.h"

class CookingList : public GameObject
{
public:
	CookingList();
	~CookingList();

	/// <summary>
	/// 料理の名前リスト。
	/// </summary>
	enum cookingList
	{
		enTomatoSoup,		//トマトスープ。
		enOnionSoup,		//玉ねぎスープ。
		encookingListNum	//料理名数。
	};

private:

	int m_materialNum = 0;		//料理に必要な材料の数。

	cookingList m_dishName = encookingListNum;		//料理名。

};

