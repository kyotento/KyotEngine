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

	int m_playerNum = 0;				//�v���C���[�̐��B
	static const int m_playerNumLimit = 4;			//�v���C���[������B

	Player* m_player[m_playerNumLimit] = { nullptr };			//�v���C���[�B
};
