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
/// �H�ו��𐶐�����N���X�B
/// </summary>
/// <param name="a">�R���g���[���[�ԍ�</param>
	Onion* NewFood(int a);

private:

	Player* m_player = nullptr;

};

