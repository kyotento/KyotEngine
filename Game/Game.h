#pragma once
#include "Title.h"
#include "Player.h"
#include "StageBase.h"
#include "Stage_1.h"
#include "Player_1.h"
#include "Player_2.h"
#include "Gauge.h"

class Title;
class Player;
class Player_1;
class Player_2;
class Stage_1;
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
	Player_1* m_player_1 = nullptr;				//プレイヤー1。
	Player_2* m_player_2 = nullptr;				//プレイヤー2。
	Stage_1* m_stage_1 = nullptr;				//ステージ１。
	Gauge* m_gauge = nullptr;

};

