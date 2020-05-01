#pragma once
#include "Title.h"
#include "Player.h"
#include "StageBase.h"
#include "Stage_1.h"
#include "Timer.h"
#include "Score.h"
#include "OrderGenerations.h"
#include "PlayerGenerations.h"
#include "StartCountdown.h"
#include "StageGeneration.h"

class Title;
class StageGeneration;
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
	/// <param name="deleteFlag">�^�C�g����Delete���ꂽ��</param>
	void SetTitleDeleteFlag(bool deleteFlag)
	{
		m_titleDeleteFlag = deleteFlag;
	}

private:

	bool m_titleDeleteFlag = false;				//�^�C�g����Delete���ꂽ���B
	bool m_firstPlay = false;					//���[�v���Ă��Ȃ����B

	Title* m_title = nullptr;					//�^�C�g���B
	Player* m_player = nullptr;					//�v���C���[�̊��N���X�B
	Stage_1* m_stage_1 = nullptr;				//�X�e�[�W�P�B
	Timer* m_timer = nullptr;					//�^�C�}�[�B
	Score* m_score = nullptr;					//�X�R�A�B
	OrderGenerations* m_orderGenerations = nullptr;			//�����V�[�g�B
	PlayerGenerations* m_playerGenerations = nullptr;		//�v���C���[�����N���X�B
	StartCountdown* m_startCountDown = nullptr;				//�Q�[�����n�܂�O�̏����B
	StageGeneration* m_stageGeneration = nullptr;			//�X�e�[�W�𐶐����鏈���B

	FontRender* m_fontRender = nullptr;		//���B

};

