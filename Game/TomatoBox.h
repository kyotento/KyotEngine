/// <summary>
/// �g�}�g�������Ă���{�b�N�X�B
/// </summary>
#pragma once
#include "FoodBox.h"
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
	/// <param name="controllerNum">�R���g���[���[�ԍ�</param>
	Tomato* NewFood(int controllerNum);

protected:


private:

	Player* m_player = nullptr;

};

