#include "stdafx.h"
#include "Cuisine.h"
#include "Belongings.h"

Cuisine::Cuisine()
{
}


Cuisine::~Cuisine()
{
}


bool Cuisine::Start()
{

	return true;
}

//�X�[�v�𐶐����鏈���B
void Cuisine::NewSoup(int FoodType)
{
	if (FoodType == Belongings::enTomato) {			//�g�}�g���������B
		m_skinModelRender->Init(L"Assets/modelData/Cuisine/tomato_soup.cmo");			//�g�}�g�X�[�v�𐶐�����B
		m_skinModelRender->SetPosition(m_position);										//���W���w�肷��B
	}	

	if (FoodType == Belongings::enOnion) {			//�ʂ˂����������B
		m_skinModelRender->Init(L"Assets/modelData/Cuisine/onion_soup.cmo");			//�ʂ˂��X�[�v�𐶐�����B
		m_skinModelRender->SetPosition(m_position);										//���W���w�肷��B
	}
}

void Cuisine::Update()
{
	m_skinModelRender->SetPosition(m_position);			//���W���X�V����B

}