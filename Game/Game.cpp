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
		m_player = NewGO<Player>(0, "player");
		m_stage_1 = NewGO<Stage_1>(0, "stage_1");
		m_titleDeleteFlag = false;
	}

}