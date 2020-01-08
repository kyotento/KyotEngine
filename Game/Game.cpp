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
	m_title = NewGO<Title>(0, "title");			//タイトルを生成する。
	camera2d.SetUpdateCameraMatrix(0);			//2Dカメラを平行投影に。	
	return true;
}


void Game::Update()
{
	//PhysicsWorld().SetDebugDrawMode(1);
	
	//中でやってることは仮。
	if (m_titleDeleteFlag)			//タイトルが消えた時。
	{
	//	m_player = NewGO<Player>(0, "player");
		m_playerGenerations = NewGO<PlayerGenerations>(0, "playergnerations");			//プレイヤー生成処理。
		m_stage_1 = NewGO<Stage_1>(0, "stage_1");										//ステージ１生成。
		m_timer = NewGO<Timer>(0, "timer");												//タイマー生成。
		m_score = NewGO<Score>(0, "score");												//スコア生成。
		m_orderGenerations = NewGO<OrderGenerations>(0, "orderGenerations");			//注文シート生成。
		m_titleDeleteFlag = false;														//生成したのでフラグを返す。
	}
}