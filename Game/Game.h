#pragma once
#include "Title.h"
#include "Player.h"

class Title;
class Player;
class Game : public GameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();

	void SetTitleDeleteFlag(bool a)
	{
		m_titleDeleteFlag = a;
	}


private:

	bool m_titleDeleteFlag = false;				//タイトルがDeleteされたか。

	Title* m_title = nullptr;					//タイトル。
	Player* m_player = nullptr;					//プレイヤーの基底クラス。

};

