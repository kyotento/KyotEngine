#pragma once
#include "Stage_1.h"
#include "StartCountdown.h"
#include "PlayerGenerations.h"
#include "Timer.h"
#include "Score.h"
#include "OrderGenerations.h"
#include "GameCamera.h"

class StageGeneration : public GameObject
{
public:
	StageGeneration();
	~StageGeneration();

	bool Start();

	/// <summary>
	/// �X�e�[�W�𐶐����鏈���B
	/// </summary>
	/// <param name="stageNum">�X�e�[�W�ԍ�</param>
	void StageGene(int stageNum);


private:

	Stage_1* m_stage_1 = nullptr;			//�X�e�[�W�P�B
	StartCountdown* m_startCoundDown = nullptr;			//�X�e�[�W�J�E���g�_�E���B
	PlayerGenerations* m_playerGenerations = nullptr;	//�v���C���[�𐶐�����N���X�B
	Timer* m_timer = nullptr;							//�^�C�}�[�N���X�B
	Score* m_score = nullptr;							//�X�R�A�N���X�B
	OrderGenerations* m_orderGenerations = nullptr;		//�����V�[�g�����N���X�B
	GameCamera* m_gamecamera = nullptr;					//�Q�[���J�����B

};

