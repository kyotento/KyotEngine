#include "stdafx.h"
#include "FoodSheetGenerations.h"

namespace {
	float XU = 120.f;		//�摜��X�X�P�[���B
	float YV = 80.f;		//�摜��Y�X�P�[���B
}

FoodSheetGenerations::FoodSheetGenerations()
{
}


FoodSheetGenerations::~FoodSheetGenerations()
{
	DeleteGO(m_spriteRender);
}


bool FoodSheetGenerations::Start()
{
	return true;
}

//�H�ו��V�[�g�̐��������B
void FoodSheetGenerations::FoodSheetGeneration(int FoodTypeNum)
{
	for (int i = 0; i < FoodTypeNum; i++)
	{
		m_spriteRender = NewGO<SpriteRender>(0, "sprite");
		m_spriteRender->Init(L"Assets/sprite/Food_Sheet3.dds", XU, YV);
		//m_spriteRender->SetPosition(m_position);
		//m_spriteRender->SetScale(m_scale);
		//m_spriteRender->SetRotation(m_rotation);
		SheetPos(FoodTypeNum);
	}
}

void FoodSheetGenerations::SheetPos(int FoodTypeNum)
{
	if (FoodTypeNum == 1) {		//�H�ו������ނ̂Ƃ��B
		m_spriteRender->SetPosition(m_position);
		m_spriteRender->SetScale(m_scale);
		m_spriteRender->SetRotation(m_rotation);
	}
	//todo ���@�ޗ������ވȏ�̂Ƃ��v�̃V�[�g�̐����������ł��Ă��Ȃ��̂ō쐬����B
	else {					//�H�ו������ވȏ�̂Ƃ��B
		//��x�����ĂԁB
		if (m_changeScaleFlag == false) {			//�X�P�[����Y���W��ύX���Ă��Ȃ���΁B
			m_scale.x = m_scaleX / FoodTypeNum;		//�X�P�[�����v�Z�B	
			m_changeScaleFlag = true;				//�ύX�����̂Ńt���O��Ԃ��B
		}

		for (int i = 0; i <= FoodTypeNum; i++) {			//�H�ו��̎�ނ������[�v����B
			float x;
			if (FoodTypeNum == 1) {
				x = XU / FoodTypeNum / 2;
				if (i == 0) {
					m_position.x -= x;
				}
				if (i == 1) {
					m_position.x += x * 2;
				}
			}

			m_spriteRender->SetPosition(m_position);
			m_spriteRender->SetScale(m_scale);			//�X�P�[�������B
			m_spriteRender->SetRotation(m_rotation);		//��]�����B
		}
	}
}

void FoodSheetGenerations::Update()
{
	if (m_spriteRender != nullptr) {
		m_spriteRender->SetPosition(m_position);		//���W�X�V�B
	}
	m_position.y = m_y;
}