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
	m_dishName = enTomatoSoup;

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
		m_materialNum = 1;			//�����ɕK�v�ȐH�ו��̎�ށB
	}
}

void CookingList::Update()
{
	CookingInformations();
}