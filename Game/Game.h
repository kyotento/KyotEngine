#pragma once
#include "Title.h"
#include "Player.h"
#include "StageBase.h"
#include "Stage_1.h"
#include "Gauge.h"
#include "Timer.h"
#include "Score.h"
#include "OrderSheet.h"
#include "OrderGenerations.h"

class Title;
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
	Stage_1* m_stage_1 = nullptr;				//�X�e�[�W�P�B
	Gauge* m_gauge = nullptr;
	Timer* m_timer = nullptr;					//�^�C�}�[�B
	Score* m_score = nullptr;					//�X�R�A�B
	OrderSheet* m_orderSheet = nullptr;
	OrderGenerations* m_orderGenerations = nullptr;

};

