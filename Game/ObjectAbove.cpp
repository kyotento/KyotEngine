#include "stdafx.h"
#include "ObjectAbove.h"
#include "Kitchen.h"

ObjectAbove::ObjectAbove()
{
}


ObjectAbove::~ObjectAbove()
{
}

//置けるものの座標を指定。
void ObjectAbove::PutThings(Belongings* belong)
{
	CVector3 PutObjPos = m_position;				//物が受けるオブジェクトの座標を代入。
	PutObjPos.y += 70.f;							//座標調整。
	belong->SetPosition(PutObjPos);					//持てる物の座標を指定。
	m_belongings = belong;							//m_belongingsに持てる物のインスタンスを代入。

}

//汚れたお皿の座標を指定。
void ObjectAbove::SetDirtyDishPos(Belongings* belongings)
{
	CVector3 PutDirtyDishPos = m_position;			//物が置けるオブジェクトの座標を代入。(お皿洗い場)。
	PutDirtyDishPos.z -= 80.f;						//位置調整。
	PutDirtyDishPos.y += 30.f;						//位置調整。
	belongings->SetPosition(PutDirtyDishPos);		//汚れたお皿の座標を指定。
	m_belongingsDirtyDIsh = belongings;				//m_belongingsDirtyDIshに汚れたお皿のインスタンスを代入。
}

//お皿の座標を指定。
void ObjectAbove::SetDishPos(Belongings* belongings)
{
	CVector3 PutDishPos = m_position;				//物が置けるオブジェクトの座標を代入。(お皿洗い場)。
	PutDishPos.y += 70.f;							//位置調整。
	PutDishPos.z += 70.f;							//位置調整。
	belongings->SetPosition(PutDishPos);			//お皿の座標を指定。
	m_belongings = belongings;						//m_belongingsにお皿のインスタンスを代入。
}


void ObjectAbove::TakeThings(Belongings* &belong)
{
	belong = m_belongings;
}

void ObjectAbove::TakeThingsDirtyDish(Belongings* &belong)
{
	belong = m_belongingsDirtyDIsh;
}

//todo 使わんかも。
void ObjectAbove::SetGaugePosition(Gauge* gauge)
{
	CVector3 GaugePos = m_position;
	GaugePos.y -= 30.f;
	gauge->SetPosition(GaugePos);
//	m_gauge = gauge;

}
