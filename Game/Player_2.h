#pragma once
#include "Player.h"

class Player_2 : public Player
{
public:
	Player_2();
	~Player_2();

	bool Start();
	void Update();

private:

	int m_controllerNumber = 1;

};

