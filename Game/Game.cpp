#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}
//TODO�@�p���g�����������Ƃ�������Ă��܂��B

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
	
	//���ł���Ă邱�Ƃ͉��B
	if (m_titleDeleteFlag)
	{
		m_player = NewGO<Player>(0, "player");
		m_stage_1 = NewGO<Stage_1>(0, "stage_1");
		m_timer = NewGO<Timer>(0, "timer");
		m_score = NewGO<Score>(0, "score");
	//	m_orderSheet = NewGO<OrderSheet>(0, "ored");
		m_titleDeleteFlag = false;
	}

}