#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}


Game::~Game()
{
}

bool Game::Start()
{
	m_title = NewGO<Title>(0, "title");

	return true;
}


void Game::Update()
{
	//PhysicsWorld().SetDebugDrawMode(1);
	
	//íÜÇ≈Ç‚Ç¡ÇƒÇÈÇ±Ç∆ÇÕâºÅB
	if (m_titleDeleteFlag)
	{
		m_player_1 = NewGO<Player_1>(0, "player");
	//	m_player_2 = NewGO<Player_2>(0, "player");
		m_stage_1 = NewGO<Stage_1>(0, "stage_1");
	//	m_gauge = NewGO<Gauge>(0, "gauge");
		m_titleDeleteFlag = false;
	}

}