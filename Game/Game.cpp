#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}
//TODO　継承使いすぎたことを後悔しています。

Game::~Game()
{
}

bool Game::Start()
{
	m_title = NewGO<Title>(0, "title");
	camera2d.SetUpdateCameraMatrix(0);
	return true;
}


void Game::Update()
{
	//PhysicsWorld().SetDebugDrawMode(1);
	
	//中でやってることは仮。
	if (m_titleDeleteFlag)
	{
	//	m_player = NewGO<Player>(0, "player");
		m_playerGenerations = NewGO<PlayerGenerations>(0, "playergnerations");
		m_stage_1 = NewGO<Stage_1>(0, "stage_1");
		m_timer = NewGO<Timer>(0, "timer");
		m_score = NewGO<Score>(0, "score");
		m_orderGenerations = NewGO<OrderGenerations>(0, "orderGenerations");
		m_titleDeleteFlag = false;
	}
}