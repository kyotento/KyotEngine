#pragma once
#include "character/CharacterController.h"

class Player1 : public GameObject
{
public:
	Player1();
	~Player1();

	bool Start();
	void Update();
	void Draw();

private:
	SkinModel* m_model;									//スキンモデル。

};

