#include "stdafx.h"
#include "Result.h"
namespace {
	float m_sheet_w = 360.f;				//�V�[�g�̉摜�̕��B
	float m_sheet_h = 540.f;				//�V�[�g�̉摜�̍����B
	float m_star_w = 80.f;					//���̉摜�̕��B
	float m_star_h = 80.f;					//���̉摜�̍����B

}

//todo �}�W�b�N�i���o�[�͂��ׂĉ��B

Result::Result()
{
}


Result::~Result()
{
	if (m_spriteRenderSheet != nullptr) {				//�V�[�g����������Ă���Ƃ��B
		DeleteGO(m_spriteRenderSheet);					//�V�[�g�������B
	}
	for (int i = 0; i < m_starNum; i++) {				//���̔z�񕪃��[�v����B
		if (m_spriteRenderStar[i] != nullptr) {			//������������Ă�����B
			DeleteGO(m_spriteRenderStar[i]);			//���������B
			m_spriteRenderStar[i] = nullptr;			//�C���X�^���X��j���B
		}
	}
}


bool Result::Start()
{

	m_spriteRenderSheet = NewGO<SpriteRender>(0, "sprite");										//�X�v���C�g�N���X�𐶐��B
	m_spriteRenderSheet->Init(L"Assets/sprite/result_sheet.dds", m_sheet_w, m_sheet_h);			//�V�[�g�̏������B
	m_spriteRenderSheet->SetPosition(m_positionSheet);											//���W���������B
	m_spriteRenderSheet->SetScale(m_scaleSheet);												//�X�P�[�����������B

	m_positionStar[0] = m_positionSheet;			//��ڂ̐��̍��W�ɃV�[�g�̍��W�����B
	m_positionStar[0].x -= 80.f;					//���Ɉړ�����B
	m_positionStar[0].y -= 90.f;					//���Ɉړ�����B

	for (int i = 0; i < m_starNum; i++) {			//�������鐯�̐������[�v����B
		m_spriteRenderStar[i] = NewGO<SpriteRender>(1, "sprite");								//�X�v���C�g�N���X�𐶐��B
		m_spriteRenderStar[i]->Init(L"Assets/sprite/black_star.dds", m_star_w, m_star_h);		//���̏�����(�͂��߂͍�����)�B
		m_spriteRenderStar[i]->SetPosition(m_positionStar[i]);									//���W���������B
		m_spriteRenderStar[i]->SetScale(m_scaleStar[i]);										//�X�P�[�����������B

		if (i <= m_starNum - 1) {					//���̔z�񂪑��݂�����B
			m_positionStar[i + 1] = m_positionStar[i];											//���̐��̍��W�ɑO�̐��̍��W�����B
			m_positionStar[i + 1].x += 80.f;													//�E�Ɉړ�����B
		}
	}

	return true;
}


void Result::Update()
{

}