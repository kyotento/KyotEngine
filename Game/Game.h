#pragma once
#include "Title.h"
#include "Player.h"
#include "StageBase.h"
#include "Stage_1.h"
#include "Gauge.h"
#include "Timer.h"
#include "Score.h"
#include "OrderSheet.h"
#include "OrderGenerations.h"

class Title;
class Game : public GameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();

	/// <summary>
	/// タイトルがDeleteされたかどうかをSetする。
	/// </summary>
	/// <param name="a">タイトルがDeleteされたか</param>
	void SetTitleDeleteFlag(bool a)
	{
		m_titleDeleteFlag = a;
	}


private:


	bool m_titleDeleteFlag = false;				//タイトルがDeleteされたか。

	Title* m_title = nullptr;					//タイトル。
	Player* m_player = nullptr;					//プレイヤーの基底クラス。
	Stage_1* m_stage_1 = nullptr;				//ステージ１。
	Gauge* m_gauge = nullptr;
	Timer* m_timer = nullptr;					//タイマー。
	Score* m_score = nullptr;					//スコア。
	OrderSheet* m_orderSheet = nullptr;
	OrderGenerations* m_orderGenerations = nullptr;

};

