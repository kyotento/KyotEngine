#pragma once
#include "Title.h"
#include "Player.h"
#include "StageBase.h"
#include "Stage_1.h"
#include "Player_1.h"
#include "Player_2.h"
#include "Gauge.h"

class Title;
class Player;
class Player_1;
class Player_2;
class Stage_1;
class Game : public GameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();

	/// <summary>
	/// �^�C�g����Delete���ꂽ���ǂ�����Set����B
	/// </summary>
	/// <param name="a">�^�C�g����Delete���ꂽ��</param>
	void SetTitleDeleteFlag(bool a)
	{
		m_titleDeleteFlag = a;
	}


private:


	bool m_titleDeleteFlag = false;				//�^�C�g����Delete���ꂽ���B

	Title* m_title = nullptr;					//�^�C�g���B
	Player* m_player = nullptr;					//�v���C���[�̊��N���X�B
	Player_1* m_player_1 = nullptr;				//�v���C���[1�B
	Player_2* m_player_2 = nullptr;				//�v���C���[2�B
	Stage_1* m_stage_1 = nullptr;				//�X�e�[�W�P�B
	Gauge* m_gauge = nullptr;

};

