#include "stdafx.h"
#include "ObjectAbove.h"


ObjectAbove::ObjectAbove()
{
}


ObjectAbove::~ObjectAbove()
{
}

void ObjectAbove::PutThings(Belongings* belong)
{
	CVector3 PutObjPos = m_position;
	PutObjPos.y += 70.f;
	belong->SetPosition(PutObjPos);
	m_belongings = belong;		

}

void ObjectAbove::TakeThings(Belongings* &belong)	//�|�C���^�̃|�C���^���Q�ƁB
{
	belong = m_belongings;
}

//todo �g��񂩂��B
void ObjectAbove::SetGaugePosition(Gauge* gauge)
{
	CVector3 GaugePos = m_position;
	GaugePos.y -= 30.f;
	gauge->SetPosition(GaugePos);
//	m_gauge = gauge;

}