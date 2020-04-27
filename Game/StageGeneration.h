#pragma once
#include "Stage_1.h"
#include "StartCountdown.h"
#include "PlayerGenerations.h"
#include "Timer.h"
#include "Score.h"
#include "OrderGenerations.h"
#include "GameCamera.h"

class StageGeneration : public GameObject
{
public:
	StageGeneration();
	~StageGeneration();

	bool Start();

	/// <summary>
	/// ステージを生成する処理。
	/// </summary>
	/// <param name="stageNum">ステージ番号</param>
	void StageGene(int stageNum);


private:

	Stage_1* m_stage_1 = nullptr;			//ステージ１。
	StartCountdown* m_startCoundDown = nullptr;			//ステージカウントダウン。
	PlayerGenerations* m_playerGenerations = nullptr;	//プレイヤーを生成するクラス。
	Timer* m_timer = nullptr;							//タイマークラス。
	Score* m_score = nullptr;							//スコアクラス。
	OrderGenerations* m_orderGenerations = nullptr;		//注文シート生成クラス。
	GameCamera* m_gamecamera = nullptr;					//ゲームカメラ。

};

