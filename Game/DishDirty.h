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

private:

	int m_dirtyDishNum = 1;			//‰˜‚ê‚½‚¨M‚Ì”B

	typedef std::list<SkinModelRender*>DishDirtyList;
	DishDirtyList m_dishDirtyList;

};

