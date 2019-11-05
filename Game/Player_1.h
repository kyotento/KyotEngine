#pragma once
#include "Player.h"

class Player_1 : public Player 
{
public:
	Player_1();
	~Player_1();

	bool Start();
	void Update();

private:

	int m_controllerNumber = 0;


};

