/// <summary>
/// ���ꂽ���M�B
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
	/// ����Ă��邨�M�̐��𑝂₷�����B
	/// </summary>
	void AddDish();

private:

	int m_dirtyDishNum = 1;			//���ꂽ���M�̐��B

	typedef std::list<SkinModelRender*>DishDirtyList;
	DishDirtyList m_dishDirtyList;

};

