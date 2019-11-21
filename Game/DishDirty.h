/// <summary>
/// ‰˜‚ê‚½‚¨MB
/// </summary>
#pragma once
#include "Belongings.h"

class DishDirty : public Belongings
{
public:
	DishDirty();
	~DishDirty();

	bool Start();
	void Update();

	/// <summary>
	/// æ‚Á‚Ä‚¢‚é‚¨M‚Ì”‚ğ‘‚â‚·ˆ—B
	/// </summary>
	void AddDish();

	/// <summary>
	/// æ‚Á‚Ä‚¢‚é‚¨M‚Ì”‚ğŒ¸‚ç‚·ˆ—B
	/// </summary>
	void DeleteDishs();

	/// <summary>
	/// ‰˜‚ê‚½‚¨M‚Ì”‚ğİ’è‚·‚éB
	/// </summary>
	/// <param name="dirtyDishNum">‰˜‚ê‚½‚¨M‚Ì”</param>
	void SetDirtyDishNum(int dirtyDishNum)
	{
		m_dirtyDishNum = dirtyDishNum;
	}

	/// <summary>
	/// ‰˜‚ê‚½‚¨M‚Ì”‚ğæ“¾‚·‚éB
	/// </summary>
	/// <returns>‰˜‚ê‚½‚¨M‚Ì”</returns>
	int GetDirtyDishNum()
	{
		return m_dirtyDishNum;
	}

private:

	int m_dirtyDishNum = 0;			//‰˜‚ê‚½‚¨M‚Ì”B

	typedef std::list<SkinModelRender*>DishDirtyList;
	DishDirtyList m_dishDirtyList;

};

