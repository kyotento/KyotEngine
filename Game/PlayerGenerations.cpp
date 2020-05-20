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
	m_playerNum = 2;		//todo ゲーム側で指定できるようにする。

	m_position.x -= 200.f;	//プレイヤー座標を決め打ち。

	//プレイヤーの生成。
	for (int i = 0; i < m_playerNum; i++) {
		m_player[i] = NewGO<Player>(0, "player");
		m_player[i]->SetControllerNumber(i);
		m_player[i]->SetPosition(m_position);
		m_position.x += 200.f;
	}

	return true;
}

void PlayerGenerations::Update()
{

}