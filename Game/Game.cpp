#include "stdafx.h"
#include "Game.h"
#include "Fade.h"
#include "Bus.h"
#include "GameCamera.h"
#include "StageSelect.h"

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
	if (m_stageGeneration != nullptr) {
		DeleteGO(m_stageGeneration);
	}

	return true;
}

void Game::Update()
{
	//todo 中でやってることは仮。
	//実際はステージセレクト画面へ。
	if (m_titleDeleteFlag)			//タイトルが消えた時。
	{
		GameCamera* m_gamecamera = NewGO<GameCamera>(0, "gamecamera");

		//m_startCountDown = NewGO<StartCountdown>(0, "startcountdown");					//ゲーム開始前の処理。
		//m_playerGenerations = NewGO<PlayerGenerations>(0, "playergnerations");			//プレイヤー生成処理。
		//m_stage_1 = NewGO<Stage_1>(0, "stage_1");										//ステージ１生成。。
		//m_timer = NewGO<Timer>(0, "timer");												//タイマー生成
		//m_score = NewGO<Score>(0, "score");												//スコア生成。
		//m_orderGenerations = NewGO<OrderGenerations>(0, "ordergenerations");			//注文シート生成。


		//Bus* bus = NewGO<Bus>(0, "bus");

//ステージセレクト試作段階。

		StageSelect* stageSelect = NewGO<StageSelect>(0, "stageselect");
		m_stageGeneration = NewGO<StageGeneration>(0, "stagegeneration");			//ステージ生成クラス。

		m_titleDeleteFlag = false;														//生成したのでフラグを返す。
	}
}