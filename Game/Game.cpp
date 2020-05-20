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
	//ステージセレクト画面への遷移。
	if (m_titleDeleteFlag)			//タイトルが消えた時。
	{
		if (m_firstPlay == false) {			//ゲームループしたときにゲームカメラを再生成しないようにするためのフィルタ。
			GameCamera* m_gamecamera = NewGO<GameCamera>(0, "gamecamera");
			m_firstPlay = true;
		}
		
	//ステージセレクト試作段階。

		StageSelect* stageSelect = NewGO<StageSelect>(0, "stageselect");
		m_stageGeneration = NewGO<StageGeneration>(0, "stagegeneration");			//ステージ生成クラス。

		m_titleDeleteFlag = false;													//生成したのでフラグを返す。
	}
}