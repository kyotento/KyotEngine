#include "stdafx.h"
#include "Dish.h"
#include "Kitchen.h"

Dish::Dish()
{
	//���M�ł���Ƃ����ݒ�B
	m_identification = enDish;
}


Dish::~Dish()
{
//	DeleteGO(m_skinModelRender);
}

bool Dish::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//�������B
	m_skinModelRender->SetPosition(m_position);							//���W���w��B
	m_skinModelRender->SetRotation(m_rotation);							//��]���w��B

	return true;
}

//�����̊Ǘ��B
void Dish::PutDish(int FoodType)
{
	m_cuisine = NewGO<Cuisine>(0, "cuisine");			//�����N���X��New����B
	m_cuisine->SetPosition(m_position);					//�X�[�v�̍��W���X�V����B
	m_cuisine->NewSoup(FoodType);								//�X�[�v�𐶐�����B
}

//��ԕω��ɂ�郂�f���̕ύX�B
void Dish::DishModelChange()
{
	if (m_oldDishState != m_dishState) {			//��Ԃ��ω�������(���t���[������������Əd�����������ǉ�)�B

		switch (m_dishState)			//��ԕω��B
		{
		case endefault:			//���ꂢ�Ȃ��M�̂Ƃ��B

			m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//���ꂢ�Ȃ��M�B

			break;

		case enSomethingOnBoard:		//���M�ɉ���(����)������Ă���Ƃ��B

			m_skinModelRender->Init(L"Assets/modelData/Dish/Dish.cmo");			//���ꂢ�Ȃ��M�B

			break;

		}
	}

	m_oldDishState = m_dishState;			//���M�̏�Ԃ����B
}

//���M���X�g�ɂ��M��ǉ�����B
void Dish::AddDishList()
{
	m_dishListNum += 1;				//���M�̐��𑝂₷�B
	m_dishList.emplace_back(NewGO<SkinModelRender>(0, "skinmodel"));		//�V�������M�𐶐�����B
	m_dishList.back()->Init(L"Assets/modelData/Dish/Dish.cmo");				//���M�B
	m_dishList.back()->SetPosition(m_position);								//���W���w��B
}

void Dish::DeleteDishList(Kitchen* kitchen)
{
	if (m_dishListNum > 0) {				//���M���X�g�̐����Q�ȏ�̂Ƃ��B
		m_dishListNum -= 1;					//���M�̐������炷�B
		DeleteGO(m_dishList.back());		//��ԍŌ�ɐ����������M�������B
		m_dishList.pop_back();				//��ԍŌ�̃��X�g�̗v�f��������B
	}
	else{
		kitchen->DeleteDishInstance();		//���M�̃C���X�^���X�������B
		DeleteGO(this);						//���M���N���X���Ə����B
	}
}

void Dish::Update()
{
	m_skinModelRender->SetPosition(m_position);			//���W�̍X�V�B

	DishModelChange();			//��ԕω��ɂ�郂�f���̕ύX�B

	if (m_cuisine != nullptr) {					//�X�[�v���������Ă���Ƃ��B
		m_cuisine->SetPosition(m_position);		//�X�[�v�̍��W���X�V����B
	}

	int y = 1;
	for (auto& model : m_dishList) {			//���X�g�̐������[�v����B�@
		model->SetPosition(m_position + CVector3::Up()*y*7.0f);		//Y���W�������グ�Ă��B�@	
		y++;		//Y���X�V�B
	}

}