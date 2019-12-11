#include "stdafx.h"
#include "ObjectAbove.h"
#include "Kitchen.h"

ObjectAbove::ObjectAbove()
{
}


ObjectAbove::~ObjectAbove()
{
}

//�u������̂̍��W���w��B
void ObjectAbove::PutThings(Belongings* belong)
{
	CVector3 PutObjPos = m_position;				//�����󂯂�I�u�W�F�N�g�̍��W�����B
	PutObjPos.y += 70.f;							//���W�����B
	belong->SetPosition(PutObjPos);					//���Ă镨�̍��W���w��B
	m_belongings = belong;							//m_belongings�Ɏ��Ă镨�̃C���X�^���X�����B

}

//���ꂽ���M�̍��W���w��B
void ObjectAbove::SetDirtyDishPos(Belongings* belongings)
{
	CVector3 PutDirtyDishPos = m_position;			//�����u����I�u�W�F�N�g�̍��W�����B(���M�􂢏�)�B
	PutDirtyDishPos.z -= 80.f;						//�ʒu�����B
	PutDirtyDishPos.y += 30.f;						//�ʒu�����B
	belongings->SetPosition(PutDirtyDishPos);		//���ꂽ���M�̍��W���w��B
	m_belongingsDirtyDIsh = belongings;				//m_belongingsDirtyDIsh�ɉ��ꂽ���M�̃C���X�^���X�����B
}

//���M�̍��W���w��B
void ObjectAbove::SetDishPos(Belongings* belongings)
{
	CVector3 PutDishPos = m_position;				//�����u����I�u�W�F�N�g�̍��W�����B(���M�􂢏�)�B
	PutDishPos.y += 70.f;							//�ʒu�����B
	PutDishPos.z += 70.f;							//�ʒu�����B
	belongings->SetPosition(PutDishPos);			//���M�̍��W���w��B
	m_belongings = belongings;						//m_belongings�ɂ��M�̃C���X�^���X�����B
}


void ObjectAbove::TakeThings(Belongings* &belong)
{
	belong = m_belongings;
}

void ObjectAbove::TakeThingsDirtyDish(Belongings* &belong)
{
	belong = m_belongingsDirtyDIsh;
}

//todo �g��񂩂��B
void ObjectAbove::SetGaugePosition(Gauge* gauge)
{
	CVector3 GaugePos = m_position;
	GaugePos.y -= 30.f;
	gauge->SetPosition(GaugePos);
//	m_gauge = gauge;

}
