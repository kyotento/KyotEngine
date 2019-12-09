#include "stdafx.h"
#include "DishHold.h"
#include "Delivery.h"

DishHold::DishHold()
{
}


DishHold::~DishHold()
{
}

bool DishHold::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/DishHold/DishHold.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	m_skinModelRenderCollidion = NewGO<SkinModelRender>(0, "collidion");
	m_skinModelRenderCollidion->Init(L"Assets/modelData/ColidionBox/collidionBox.cmo");
	m_skinModelRenderCollidion->SetPosition(m_position);
	m_skinModelRenderCollidion->SetScale(m_scale);
	m_skinModelRenderCollidion->SetRotation(m_rotation);

	m_physicsStaticObject.CreateMeshObject(m_skinModelRenderCollidion->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollidion);

	m_physicsStaticObject.SetUserIndex(enDishHold);
	m_physicsStaticObject.SetUserPointer(this);

	m_dishPosition.x = m_position.x;
	m_dishPosition.z = m_position.z;
	m_dishPosition.y = m_position.y += 70.f;

	return true;
}

void DishHold::NumberOfDished()
{
	if (m_oldDishNum < m_dishNum) {		//���M�̐������������B

		//���M����ȏ㐶������Ă���Ƃ��̏����B
		if (m_dishDirty != nullptr)
		{
			m_dishDirty->AddDish();			//���M�𑝂₷�����B
		}

		//���M�������������ĂȂ��Ƃ��̏����B
		if (m_dishDirty == nullptr) {
			m_dishDirty = NewGO<DishDirty>(0, "dishdirty");		//���M�̐����B
			PutThings(m_dishDirty);								//���M�u���ɂ��M��u�������B
			m_dishDirty->SetPosition(m_dishPosition);			//���W������Ă���̂ŏ㏑�����Ă��B
			m_state = en_onObject;								//���M�u���̏�Ԃ�ύX�B
		}
	}

	m_oldDishNum = m_dishNum;			//���M�̐����ύX���ꂽ�����m�F���邽�߂ɑ���B
}

void DishHold::Update()
{
	NumberOfDished();			//���M�̐����Ǘ�����֐��B

	if (m_state == en_default)
	{
		m_dishDirty = nullptr;
	}

}
