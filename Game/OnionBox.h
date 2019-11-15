#pragma once
#include "FoodBox.h"
#include "Player.h"

class Player;
class OnionBox : public FoodBox
{
public:
	OnionBox();
	~OnionBox();

	bool Start();
	void Update();

/// <summary>
/// 食べ物を生成するクラス。
/// </summary>
/// <param name="controllerNum">コントローラー番号</param>
	Onion* NewFood(int controllerNum);

private:

	Player* m_player = nullptr;

};

