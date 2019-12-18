#include "stdafx.h"
#include "FoodSheetGenerations.h"

namespace {
	float XU = 140.f;
}

FoodSheetGenerations::FoodSheetGenerations()
{
}


FoodSheetGenerations::~FoodSheetGenerations()
{
}


bool FoodSheetGenerations::Start()
{
	return true;
}

//�H�ו��V�[�g�̐��������B
void FoodSheetGenerations::FoodSheetGeneration(int FoodTypeNum)
{
	for (int i = 0; i <= FoodTypeNum; i++)
	{
		m_spriteRender[i] = NewGO<SpriteRender>(0, "sprite");
		m_spriteRender[i]->Init(L"Assets/sprite/Food_Sheet3.dds", XU, 80.f);
		m_spriteRender[i]->SetPosition(m_position);
		m_spriteRender[i]->SetScale(m_position);
		m_spriteRender[i]->SetRotation(m_rotation);
	}
}

void FoodSheetGenerations::SheetPos(int FoodTypeNum)
{
	if (FoodTypeNum == 1) {		//�H�ו������ނ̂Ƃ��B
		m_spriteRender[0]->SetPosition(m_position);
		m_spriteRender[0]->SetScale(m_scale);
		m_spriteRender[0]->SetRotation(m_rotation);
	}

	else {					//�H�ו������ވȏ�̂Ƃ��B
		//��x�����ĂԁB
		if (m_changeScaleFlag == false) {			//�X�P�[����Y���W��ύX���Ă��Ȃ���΁B
			m_scale.y = m_scaleY / FoodTypeNum;		//�X�P�[�����v�Z�B	
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
					m_spriteRender[i]->SetPosition(m_position);
			}

			m_spriteRender[i]->SetScale(m_scale);			//�X�P�[�������B
			m_spriteRender[i]->SetRotation(m_rotation);		//��]�����B
		}
	}
}

void FoodSheetGenerations::Update()
{

}