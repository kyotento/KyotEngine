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
	m_playerNum = 2;		//todo �Q�[�����Ŏw��ł���悤�ɂ���B

	m_position.x -= 200.f;	//�v���C���[���W�����ߑł��B

	//�v���C���[�̐����B
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