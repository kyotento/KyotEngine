#pragma once
#include "FoodBox.h"/*
#include */
#include "Player.h"

class Player;
class TomatoBox : public FoodBox
{
public:
	TomatoBox();
	~TomatoBox();

	bool Start();
	void Update();

	/// <summary>
	/// 食べ物を生成するクラス。
	/// </summary>
	/// <param name="controllerNum">コントローラー番号</param>
	Tomato* NewFood(int controllerNum);

protected:


private:

	Player* m_player = nullptr;

};

