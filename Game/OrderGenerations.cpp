#include "stdafx.h"
#include "OrderGenerations.h"

namespace {
}

OrderGenerations::OrderGenerations()
{
}

OrderGenerations::~OrderGenerations()
{
}

bool OrderGenerations::Start()
{
	m_foodSheetGenerations = NewGO<FoodSheetGenerations>(3, "foodSheet");

	return true;
}

//���������B
void OrderGenerations::Generations()
{
	if (m_generationNum < m_orderNumLimit && m_order == false) {		//�����̐�������l��菭�Ȃ��Ƃ��B���A���������Ă��Ȃ��Ƃ��B
		m_orderTimer += 1.f / 60.f;					//�^�C�}�[��i�߂�B
		if (m_orderTimer >= 5.f) {					//5�b�ȏ�o�߂����Ȃ�B
			m_order = true;							//�����t���O��Ԃ��B
			m_orderTimer = 0.f;						//�^�C�}�[�����Z�b�g����B
		}
	}

	if (m_order) {			//�����t���O��true�Ȃ�B
		m_orderSheet[m_orderNumber] = NewGO<OrderSheet>(0, "orderSheet");		//�z��m_order�Ԗڂɒ����V�[�g�𐶐��B
		m_position[m_orderNumber].x = 540.f;			//X���W���w��B
		m_position[m_orderNumber].y = m_sheet_y;		//Y���W���w��B
		m_position[m_orderNumber].z = m_sheet_z;		//Z���W���w��B
		m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//���W���X�V�B

		m_generationNum += 1;		//�����������Z����B
		m_orderNumber += 1;			//�����ԍ���ύX����B
		m_order = false;			//�������ꂽ�̂Ńt���O��Ԃ��B
	}
}

//�ړ������B
void OrderGenerations::Move()
{
	for (int m_orderNumber = 0; m_orderNumber < m_orderNumLimit; m_orderNumber++) {		//�z��̐������[�v����B
		if (m_orderSheet[m_orderNumber] != nullptr) {			//�V�[�g����������Ă�����B
			if (m_position[m_orderNumber].x > m_moveLimit[m_orderNumber]) {		//���W������l�ɒB���Ă��Ȃ�������B
				m_position[m_orderNumber].x -= 20.f;			//X���W���X�V�B	
				m_position[m_orderNumber].y = m_sheet_y;		//Y���W���X�V�B
				m_position[m_orderNumber].z = m_sheet_z;		//Z���W���X�V�B
			}
			m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//�V�[�g�̍��W���X�V�B

			if (m_position[m_orderNumber].x <= m_moveLimit[m_orderNumber]) {	//���W������l�ɒB�������B

				FoodSheetGeneration(1, m_orderNumber);		//�P�͉��B
				FoodSheetPosUpdate(m_orderNumber);						//�H�ו��V�[�g�̍��W�X�V�����B
			}
		}
	}
}

//�����Ɏg�p����H�ו��������V�[�g�B
void OrderGenerations::FoodSheetGeneration(int FoodTypeNum, int genenum)
{
	if (m_foodSheetGenerationFlag[genenum] == false) {		//�H�ו��V�[�g�𐶐����Ă��Ȃ�������B
		m_foodSheetGenerations->FoodSheetGeneration(FoodTypeNum);		//�H�ו��V�[�g�𐶐��B
		m_foodSheetGenerations->SetPosition(m_position[genenum]);		//�������ꂽ�V�[�g�̍��W���w�肵�Ă��B
		m_foodPosY[genenum] = m_position[genenum].y;								//Y���W��ۑ����Ă����B

		m_foodSheetGenerationFlag[genenum] = true;			//���������̂Ńt���O��Ԃ��B
	}
}

//�H�ו��V�[�g�̍��W�X�V�����B
void OrderGenerations::FoodSheetPosUpdate(int genenum)
{
	if (m_foodPosY[genenum] >= m_foodPosYLimit) {		//���W������l�ɒB���Ă��Ȃ��Ȃ�B
		m_foodPosY[genenum] += -1.f;					//Y���W�𖇃t���[���X�V�B
	}
	if (m_foodSheetGenerationFlag) {					//��������Ă�����B
		m_foodSheetGenerations->SetPositionY(m_foodPosY[genenum]);		//���W���X�V����B
	}
}

void OrderGenerations::Update()
{
	//���������B
	Generations();
	//�ړ������B
	Move();
}

//todo �z�񂲂Ə����Ƃ��ɂ�邱��
/*
	�����t���O��Ԃ��B
	�z��̋󂢂��Ƃ�����l�߂�B
	m_foodPosY�����Z�b�g����B
*/