#include "stdafx.h"
#include "Game.h"
#include "Fade.h"
#include "Bus.h"
#include "GameCamera.h"
#include "StageSelect.h"

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
	if (m_stageGeneration != nullptr) {
		DeleteGO(m_stageGeneration);
	}

	return true;
}

void Game::Update()
{
	//�X�e�[�W�Z���N�g��ʂւ̑J�ځB
	if (m_titleDeleteFlag)			//�^�C�g�������������B
	{
		if (m_firstPlay == false) {			//�Q�[�����[�v�����Ƃ��ɃQ�[���J�������Đ������Ȃ��悤�ɂ��邽�߂̃t�B���^�B
			GameCamera* m_gamecamera = NewGO<GameCamera>(0, "gamecamera");
			m_firstPlay = true;
		}
		
	//�X�e�[�W�Z���N�g����i�K�B

		StageSelect* stageSelect = NewGO<StageSelect>(0, "stageselect");
		m_stageGeneration = NewGO<StageGeneration>(0, "stagegeneration");			//�X�e�[�W�����N���X�B

		m_titleDeleteFlag = false;													//���������̂Ńt���O��Ԃ��B
	}
}