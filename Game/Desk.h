/// <summary>
/// Š÷i‚½‚¾‚ÌŠ÷jB
/// </summary>
#pragma once
#include "level/MapChip.h"
#include "ObjectAbove.h"

class Desk : public ObjectAbove
{
public:
	Desk();
	~Desk();

	bool Start();
	void Update();
	void StateChange();


private:


};

