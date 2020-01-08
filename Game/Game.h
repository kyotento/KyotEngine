#pragma once
#include "Title.h"
#include "Player.h"
#include "StageBase.h"
#include "Stage_1.h"
#include "Timer.h"
#include "Score.h"
#include "OrderGenerations.h"
#include "PlayerGenerations.h"

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
	/// <param name="deleteFlag">タイトルがDeleteされたか</param>
	void SetTitleDeleteFlag(bool deleteFlag)
	{
		m_titleDeleteFlag = deleteFlag;
	}

private:

	bool m_titleDeleteFlag = false;				//タイトルがDeleteされたか。

	Title* m_title = nullptr;					//タイトル。
	Player* m_player = nullptr;					//プレイヤーの基底クラス。
	Stage_1* m_stage_1 = nullptr;				//ステージ１。
	Timer* m_timer = nullptr;					//タイマー。
	Score* m_score = nullptr;					//スコア。
	OrderGenerations* m_orderGenerations = nullptr;			//注文シート。
	PlayerGenerations* m_playerGenerations = nullptr;		//プレイヤー生成クラス。

};

