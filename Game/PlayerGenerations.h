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
	/// �v���C���[�̐����w�肷��B
	/// </summary>
	/// <param name="playerNum"></param>
	void SetPlayerNum(int playerNum)
	{
		m_playerNum = playerNum;
	}

private:

	int m_playerNum = 0;				//�v���C���[�̐��B
	static const int m_playerNumLimit = 4;			//�v���C���[������B
	CVector3 m_position = CVector3::Zero();			//���W�B

	Player* m_player[m_playerNumLimit] = { nullptr };			//�v���C���[�B
};

