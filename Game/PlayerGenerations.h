#pragma once
#include "GameObject.h"
#include "Player.h"

class PlayerGenerations : public GameObject
{
public:
	PlayerGenerations();
	~PlayerGenerations();

	bool Start();
	void Update();

private:

	int m_playerNum = 0;				//プレイヤーの数。
	static const int m_playerNumLimit = 4;			//プレイヤー上限数。

	Player* m_player[m_playerNumLimit] = { nullptr };			//プレイヤー。
};

