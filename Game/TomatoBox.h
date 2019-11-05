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
	/// �H�ו��𐶐�����N���X�B
	/// </summary>
	/// <param name="a">�R���g���[���[�ԍ�</param>
	Tomato* NewFood(int a);

protected:


private:

	Player* m_player = nullptr;

};

