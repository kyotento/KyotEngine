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

void Dish::PutDish()
{
	m_cuisine = NewGO<Cuisine>(0, "cuisine");			//�����N���X��New����B
	m_cuisine->NewSoup();								//�X�[�v�𐶐�����B
	m_cuisine->SetPosition(m_position);					//�X�[�v�̍��W���X�V����B
}

void Dish::DishModelChange()
{
	if (m_oldDishState != m_dishState) {			//��Ԃ��ω�������(���t���[������������Əd�����������ǉ�)�B

		switch (m_dishState)			//��ԕω��B
		{
		case endefault:

			m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");

			break;

		case endirty:

			m_skinModelRender->Init(L"Assets/modelData/Dish/DirtyDish.cmo");

			break;

		case enSomethingOnBoard:

			break;

		}

	}
	m_oldDishState = m_dishState;			//����B
}

void Dish::Update()
{
	m_skinModelRender->SetPosition(m_position);			//���W�̍X�V�B

	DishModelChange();

	if (m_cuisine != nullptr) {					//�X�[�v���������Ă���Ƃ��B
		m_cuisine->SetPosition(m_position);		//�X�[�v�̍��W���X�V����B
	}

}