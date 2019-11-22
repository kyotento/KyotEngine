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

void ObjectAbove::SetDirtyDishPos(Belongings* belongings)
{
	CVector3 PutDirtyDishPos = m_position;
	PutDirtyDishPos.z -= 80.f;
	PutDirtyDishPos.y += 30.f;
	belongings->SetPosition(PutDirtyDishPos);
	m_belongings = belongings;
}

void ObjectAbove::SetDishPos(Belongings* belongings)
{
	CVector3 PutDishPos = m_position;
	PutDishPos.y += 70.f;
	PutDishPos.z += 30.f;
	belongings->SetPosition(PutDishPos);
	m_belongings = belongings;
}


void ObjectAbove::TakeThings(Belongings* &belong)	//ポインタのポインタを参照。
{
	belong = m_belongings;
}

//todo 使わんかも。
void ObjectAbove::SetGaugePosition(Gauge* gauge)
{
	CVector3 GaugePos = m_position;
	GaugePos.y -= 30.f;
	gauge->SetPosition(GaugePos);
//	m_gauge = gauge;

}