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

	bool m_titleDeleteFlag = false;				//�^�C�g����Delete���ꂽ���B

	Title* m_title = nullptr;					//�^�C�g���B
	Player* m_player = nullptr;					//�v���C���[�̊��N���X�B

};

