#include "stdafx.h"
#include "Dish.h"


Dish::Dish()
{
	//���M�ł���Ƃ����ݒ�B
	m_identification = enDish;
}


Dish::~Dish()
{
}

bool Dish::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}

void Dish::Update()
{
	m_skinModelRender->SetPosition(m_position);			//���W�̍X�V�B

}