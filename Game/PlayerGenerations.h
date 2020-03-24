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

	/// <summary>
	/// プレイヤーの数を指定する。
	/// </summary>
	/// <param name="playerNum"></param>
	void SetPlayerNum(int playerNum)
	{
		m_playerNum = playerNum;
	}

private:

	int m_playerNum = 0;				//プレイヤーの数。
	static const int m_playerNumLimit = 4;			//プレイヤー上限数。
	CVector3 m_position = CVector3::Zero();			//座標。

	Player* m_player[m_playerNumLimit] = { nullptr };			//プレイヤー。
};

