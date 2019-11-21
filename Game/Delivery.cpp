#include "stdafx.h"
#include "Delivery.h"


Delivery::Delivery()
{
}


Delivery::~Delivery()
{
}

bool Delivery::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Delivery/derivery.cmo");
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

	m_physicsStaticObject.SetUserIndex(enDelivery);
	m_physicsStaticObject.SetUserPointer(this);

	return true;
}

void Delivery::Update()
{

	if (m_state == ObjectAbove::en_onObject)			//��������Ă���Ƃ��B
	{
		m_TimeAdvanced = true;
		m_state = en_default;

	}

	if (m_TimeAdvanced)
	{
		m_StateChangeTime += 1.f;

		if (m_StateChangeTime >= 60.f) {
			//������DishHold�ɎM��u�������B
			m_DishNum3 += 1;
			m_dishHold->SetDishNum(m_DishNum3);			//���M�̐���ݒ�B
			m_TimeAdvanced = false;
			m_StateChangeTime = 0.f;
		}
	}

}
