#pragma once
#include "character/CharacterController.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Draw();

private:
	SkinModel* m_model;									//スキンモデル。

};

