#pragma once
#include "Belongings.h"
class Dish : public Belongings
{
public:
	Dish();
	~Dish();

	bool Start();
	void Update();

	/// <summary>
	/// ‚¨M‚Ìó‘Ô‚ğæ“¾‚·‚éB
	/// </summary>
	/// <returns>‚¨M‚Ìó‘Ô</returns>
	int GetState()
	{
		return m_dishState;
	}

private:

	/// <summary>
	/// ‚¨M‚Ìó‘ÔB
	/// </summary>
	enum DishState
	{
		endefault,				//‚«‚ê‚¢‚È‚¨MB
		endirty,				//‰˜‚ê‚Ä‚éB
		enSomethingOnBoard,		//‰½‚©æ‚Á‚Ä‚¢‚é‚Æ‚«B
	};

	DishState m_dishState = endefault;			//‚¨M‚Ìó‘ÔB


};

