#pragma once
#include "ObjectAbove.h"

class DishHold : public ObjectAbove
{

public:
	DishHold();
	~DishHold();

	bool Start();
	void Update();

private:

	bool m_dishNum = 0;		//����Ă��邨�M�̐��B


};

