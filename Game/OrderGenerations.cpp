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
				m_position[m_orderNumber].x -= 20.f;				//X���W���X�V�B	
				m_position[m_orderNumber].y = m_sheet_y;		//Y���W���X�V�B
				m_position[m_orderNumber].z = m_sheet_z;		//Z���W���X�V�B
			}
			m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//�V�[�g�̍��W���X�V�B
		}
	}
}

//�����Ɏg�p����H�ו��������V�[�g�B
void OrderGenerations::FoodSheetGenerations(int FoodTypeNum)
{

}

void OrderGenerations::Update()
{
	//���������B
	Generations();
	//�ړ������B
	Move();
}
