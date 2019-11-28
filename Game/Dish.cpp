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

			m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//���ꂢ�Ȃ��M�B

			break;

		case enSomethingOnBoard:

			m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//���ꂢ�Ȃ��M�B

			break;

		}

	}
	m_oldDishState = m_dishState;			//����B
}

/// <summary>
/// ���M���X�g�ɂ��M��ǉ�����B
/// </summary>
void Dish::AddDishList()
{
	m_dishListNum += 1;
	m_dishList.emplace_back(NewGO<SkinModelRender>(0, "skinmodel"));
	m_dishList.back()->Init(L"Assets/modelData/Dish/Dish.cmo");			//���ꂽ���M�B
	m_dishList.back()->SetPosition(m_position);
}

void Dish::Update()
{
	m_skinModelRender->SetPosition(m_position);			//���W�̍X�V�B

	DishModelChange();

	if (m_cuisine != nullptr) {					//�X�[�v���������Ă���Ƃ��B
		m_cuisine->SetPosition(m_position);		//�X�[�v�̍��W���X�V����B
	}

	int y = 1;
	for (auto& model : m_dishList) {
		model->SetPosition(m_position + CVector3::Up()*y*5.0f);
		y++;
	}

}