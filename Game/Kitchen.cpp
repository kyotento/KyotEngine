#include "stdafx.h"
#include "Kitchen.h"


Kitchen::Kitchen()
{
}


Kitchen::~Kitchen()
{

}


bool Kitchen::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/kitchen/kitchen.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	m_skinModelRenderCollidion = NewGO<SkinModelRender>(0, "collidion");
	m_skinModelRenderCollidion->Init(L"Assets/modelData/ColidionBox/collidionBoxLong.cmo");
	m_skinModelRenderCollidion->SetPosition(m_position);
	m_skinModelRenderCollidion->SetScale(m_scale);
	m_skinModelRenderCollidion->SetRotation(m_rotation);

	m_physicsStaticObject.CreateMeshObject(m_skinModelRenderCollidion->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollidion);

	m_physicsStaticObject.SetUserIndex(enKitchen);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}

//���M��􂤁B
void Kitchen::DishWashing()
{
	//���M�􂢂̏�ɉ��ꂽ���M������Ƃ��B
	//todo ��@2D�̃o�O�Ȓ�������Gauge�𐶐�����B
	//�g�又�������Ċg��l���P�ɂȂ����牘�ꂽ���M�������ĐV�������M�𐶐�����B
	//todo ���@���̓Q�[�W��`��ł��Ȃ��̂ŏ������^�C�}�[�ɂ���B

	if (m_dishDirty->GetDirtyDishNum() > 0) {
		m_timerK += 1;

		if (m_timerK >= 120) {		//�Q�b�ȏソ�����Ƃ��B

			//����Ă��邨�M��1�̎��B
			if (m_dishDirty->GetDirtyDishNum() <= 1 && m_dishDirty->GetDirtyDishNum() > 0) {
				DeleteGO(m_dishDirty);						//���ꂽ���M�N���X�������B

				if (m_dish != nullptr) {			//���M������Ƃ��B

					m_dish->AddDishList();			//���M�𐶐�����B
				}

				if (m_dish == nullptr) {			//���M���Ȃ��Ƃ��B

					m_dish = NewGO<Dish>(0, "dish");			//���M�𐶐�����B
				}

				SetDishPos(m_dish);					//���M�̍��W���w��B
				m_timerK = 0;
			}

			//����Ă��鉘�ꂽ���M�̐���2�ȏ�̂Ƃ��B
			if (m_dishDirty->GetDirtyDishNum() > 1) {
				m_dishDirty->DeleteDishs();					//���ꂽ���M�������B

				if (m_dish != nullptr) {

					m_dish->AddDishList();			//���M�𐶐�����B
				}

				if (m_dish == nullptr) {

					m_dish = NewGO<Dish>(0, "dish");			//���M�𐶐�����B
				}

				SetDishPos(m_dish);
				m_timerK = 0;
			}
		}
	}
}

//���M�̃C���X�^���X�����������B
void Kitchen::DeleteDishInstance()
{
	if (m_dish != nullptr) {					//���M�̃C���X�^���X������Ƃ��B
		if (m_dish->GetDisListNum() <= 0)		//���X�g�̒��g���Ȃ��Ƃ��B
		{
			m_dish = nullptr;					//���M�̃C���X�^���X��null�ɁB
		}
	}

}

//�X�V�����B
void Kitchen::Update()
{
	if (m_dish == nullptr)			//���M�̃C���X�^���X��Null�̂Ƃ��B
	{
		m_state = en_default;			//��Ԃ���������Ă��Ȃ���ԂɁB
	}

}
