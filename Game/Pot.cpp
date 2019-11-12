#include "stdafx.h"
#include "Pot.h"


Pot::Pot()
{
}


Pot::~Pot()
{
	DeleteGO(m_skinModelRender);
}


bool Pot::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Pot/Pot.cmo");		//�������A
	m_skinModelRender->SetPosition(m_position);						//���W�w��B

	return true;
}

void Pot::Soup()
{

	if (m_potState == enTwo) {
		m_soupPos.y += 100.f;
		m_potState = enComplete;
	}
	if (m_potState == enOne) {							//�H�ו���������Ă����Ԃ̂Ƃ��B
		m_soupPos.y += 100.f;							//�H�ו����₦���悤�Ɍ����邽�߂�Y���p���グ��B
		m_potState = enTwo;								//�|�b�g�ɐH�ו���������Ă����ԁB
	}

	if (m_potState == enZero) {							//�|�b�g�ɉ��������Ă��Ȃ��Ƃ��B
		m_soupBase = NewGO<SoupBase>(0, "soup");		//�X�[�v�̕����𐶐�����B
		m_potState = enOne;								//�|�b�g�ɐH�ו���������Ă����ԂɁB
	}
}

void Pot::Update()
{
	m_skinModelRender->SetPosition(m_position);		//���W���X�V�B
	if (m_soupBase != nullptr) {
		m_soupBase->SetPosition(m_soupPos);				//�X�[�v�̍��W���w��B
	}
	//m_soupPos = m_position;		//��̍��W���X�[�v�̍��W�ɑ���B
}