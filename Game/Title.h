#pragma once
#include "Game.h"

class Game;
class Title : public GameObject
{
public:
	Title();
	~Title();

	bool Start()override;
	void Update();

private:

	CVector3 m_position = CVector3::Zero();		//座標。

	SpriteRender* m_spriteRender = nullptr;		//Sprite。
	Sound* se = nullptr;
	Pad* m_pad = nullptr;						//コントローラPadクラス。
	Game* m_game = nullptr;						//Gameクラス。

};

