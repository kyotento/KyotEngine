#include "stdafx.h"
#include "StageGeneration.h"
#include "StageSelect.h"

StageGeneration::StageGeneration()
{
}


StageGeneration::~StageGeneration()
{
}


bool StageGeneration::Start()
{

	return true;
}

//ステージを生成する処理。
void StageGeneration::StageGene(int stageNum)
{
	if (g_pad[0].IsTrigger(enButtonB)) {			//Bボタンを押したとき。

		m_startCoundDown = NewGO<StartCountdown>(0, "startcountdown");			//カウントダウンクラスの生成。
		m_playerGenerations = NewGO<PlayerGenerations>(0, "playergenerations");	//プレイヤー生成クラスの生成。
		if (stageNum == 0) {		
			m_stage_1 = NewGO<Stage_1>(0, "stage_1");								//ステージ１の生成。
		}
		m_timer = NewGO<Timer>(0, "timer");										//タイマークラスの生成。
		m_score = NewGO<Score>(0, "score");										//スコアクラスの生成。
		m_orderGenerations = NewGO<OrderGenerations>(0, "ordergenerations");		//注文シート生成クラス生成。

		StageSelect* m_stageSelect = FindGO<StageSelect>("stageselect");			//ステージセレクトマップのインスタンスを取得。
		DeleteGO(m_stageSelect);													//ステージセレクトマップを消す。
	}
}
