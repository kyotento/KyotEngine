#include "stdafx.h"
#include "CookingList.h"


CookingList::CookingList()
{
}


CookingList::~CookingList()
{
}

bool CookingList::Start()
{
	//todo ���B
//	m_dishName = enTomatoSoup;

	return true;
}

void CookingList::CookingInformations()
{
	if (m_dishName == enTomatoSoup)		//�g�}�g�X�[�v�̂Ƃ��B
	{
		m_materialNum = 3;			//�����ɕK�v�ȐH�ו��̐��B
		m_foodtype = 1;				//�����ɕK�v�ȐH�ו��̎�ށB
	}

	if (m_dishName == enOnionSoup)		//�ʂ˂��X�[�v�̂Ƃ��B
	{
		m_materialNum = 3;			//�����ɕK�v�ȐH�ו��̐��B
		m_foodtype = 1;				//�����ɕK�v�ȐH�ו��̎�ށB
	}
}

int CookingList::OrderSetting()
{
	//todo�@���ۂ̓X�e�[�W���Ƃɗ�����ς���B
	//�X�e�[�W�P�B
	float a = random().GetRandDouble();		//�O�`�P�̃����_���Ȓl��a�ɑ���B

	if (a <= 0.500f) {						//0.5�ȉ��̏ꍇ�B
		m_dishName = enTomatoSoup;			//�������g�}�g�X�[�v�ɁB
	}
	else{									//0.5���傫���Ƃ��B
		m_dishName = enOnionSoup;			//�������ʂ˂��X�[�v�ɁB
	}

	return m_dishName;			//��������Ԃ��B
}

void CookingList::Update()
{
	CookingInformations();
}