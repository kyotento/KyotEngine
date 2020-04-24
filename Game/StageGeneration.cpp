#include "stdafx.h"
#include "StageGeneration.h"
#include "StageSelect.h"

StageGeneration::StageGeneration()
{
}


StageGeneration::~StageGeneration()
{
}


bool StageGeneration::Start()
{

	return true;
}

//�X�e�[�W�𐶐����鏈���B
void StageGeneration::StageGene(int stageNum)
{
	if (g_pad[0].IsTrigger(enButtonB)) {			//B�{�^�����������Ƃ��B

		m_startCoundDown = NewGO<StartCountdown>(0, "startcountdown");			//�J�E���g�_�E���N���X�̐����B
		m_playerGenerations = NewGO<PlayerGenerations>(0, "playergenerations");	//�v���C���[�����N���X�̐����B
		if (stageNum == 0) {		
			m_stage_1 = NewGO<Stage_1>(0, "stage_1");								//�X�e�[�W�P�̐����B
		}
		m_timer = NewGO<Timer>(0, "timer");										//�^�C�}�[�N���X�̐����B
		m_score = NewGO<Score>(0, "score");										//�X�R�A�N���X�̐����B
		m_orderGenerations = NewGO<OrderGenerations>(0, "ordergenerations");		//�����V�[�g�����N���X�����B

		StageSelect* m_stageSelect = FindGO<StageSelect>("stageselect");			//�X�e�[�W�Z���N�g�}�b�v�̃C���X�^���X���擾�B
		DeleteGO(m_stageSelect);													//�X�e�[�W�Z���N�g�}�b�v�������B
	}
}
