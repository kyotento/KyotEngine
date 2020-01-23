#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}
//TODO�@�p���g�����������Ƃ�������Ă��܂��B

Game::~Game()
{
}

bool Game::Start()
{
	m_title = NewGO<Title>(0, "title");			//�^�C�g���𐶐�����B
	camera2d.SetUpdateCameraMatrix(0);			//2D�J�����𕽍s���e�ɁB

	return true;
}

void Game::Update()
{
	//todo ���ł���Ă邱�Ƃ͉��B
	//���ۂ̓X�e�[�W�Z���N�g��ʂցB
	if (m_titleDeleteFlag)			//�^�C�g�������������B
	{
		m_startCountDown = NewGO<StartCountdown>(0, "startcountdown");					//�Q�[���J�n�O�̏����B
		m_playerGenerations = NewGO<PlayerGenerations>(0, "playergnerations");			//�v���C���[���������B
		m_stage_1 = NewGO<Stage_1>(0, "stage_1");										//�X�e�[�W�P�����B
		m_timer = NewGO<Timer>(0, "timer");												//�^�C�}�[�����B
		m_score = NewGO<Score>(0, "score");												//�X�R�A�����B
		m_orderGenerations = NewGO<OrderGenerations>(0, "ordergenerations");			//�����V�[�g�����B

		m_titleDeleteFlag = false;														//���������̂Ńt���O��Ԃ��B
	}
}