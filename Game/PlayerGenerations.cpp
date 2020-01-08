#include "stdafx.h"
#include "PlayerGenerations.h"


PlayerGenerations::PlayerGenerations()
{
}


PlayerGenerations::~PlayerGenerations()
{
}

bool PlayerGenerations::Start()
{
	m_playerNum = 2;		//todo kari 

	for (int i = 0; i < m_playerNum; i++) {
		m_player[i] = NewGO<Player>(0, "player");
		m_player[i]->SetControllerNumber(i);
	}

	return true;
}

void PlayerGenerations::Update()
{

}