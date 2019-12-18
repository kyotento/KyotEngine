#include "stdafx.h"
#include "OrderGenerations.h"

namespace {
	float m_sheet_x = 600.f;
	float m_sheet_y = 310.f;
	float m_sheet_z = 0.f;
	float moveLimit = -540.f;
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
		m_position[m_orderNumber].x = 540.f;
		m_position[m_orderNumber].x = m_sheet_y;
		m_position[m_orderNumber].x = m_sheet_z;
		m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);		//���W���X�V�B

		m_generationNum += 1;			//�����������Z����B
		m_order = false;			//�������ꂽ�̂Ńt���O��Ԃ��B
	}
}

void OrderGenerations::Move()
{
	if (m_orderSheet[m_orderNumber] != nullptr) {
		if (m_position[m_orderNumber].x > moveLimit) {
			m_position[m_orderNumber].x -= 5.f;
			m_position[m_orderNumber].y = m_sheet_y;
			m_position[m_orderNumber].z = m_sheet_z;
		}
		m_orderSheet[m_orderNumber]->SetPosition(m_position[m_orderNumber]);
	}
}

void OrderGenerations::Update()
{
	//���������B
	Generations();
	//�ړ������B
	Move();
}
