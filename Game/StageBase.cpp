#include "stdafx.h"
#include "StageBase.h"

StageBase::StageBase()
{
}

StageBase::~StageBase()
{
}

bool StageBase::Start()
{

	return true;
}

//bool StageBase::LevelGeneration(LevelObjectData& objData)
//{
//	//�n�ʁB
//	if (objData.EqualObjectName(L"kari_floor") == true)
//	{
//		return false;
//	}
//
//	//���B
//	if (objData.EqualObjectName(L"Desk") == true)
//	{
//		m_desk = NewGO<Desk>(0, "desk");
//		m_desk->SetPosition(objData.position);
//		m_desk->SetRotation(objData.rotation);
//		m_desk->SetScale(objData.scale);
//	}
//
//	//���M�u���B
//	if (objData.EqualObjectName(L"DishHold") == true)
//	{
//		m_dishHold = NewGO<DishHold>(0, "dishhold");
//		m_dishHold->SetPosition(objData.position);
//		m_dishHold->SetRotation(objData.rotation);
//		m_dishHold->SetScale(objData.scale);
//	}
//
//	//�K�X�R�����B
//	if (objData.EqualObjectName(L"gas_stove") == true)
//	{
//		m_gasStove = NewGO<GasStove>(0, "gasstove");
//		m_gasStove->SetPosition(objData.position);
//		m_gasStove->SetRotation(objData.rotation);
//		m_gasStove->SetScale(objData.scale);
//	}
//
//	//�S�~���B
//	if (objData.EqualObjectName(L"DustBox") == true)
//	{
//		m_dustbox = NewGO<DustBox>(0, "dustbox");
//		m_dustbox->SetPosition(objData.position);
//		m_dustbox->SetRotation(objData.rotation);
//		m_dustbox->SetScale(objData.scale);
//
//	}
//
//	//�܂ȔB
//	if (objData.EqualObjectName(L"cutting_board") == true)
//	{
//		m_cuttingBoard = NewGO<CuttingBoard>(0, "cuttingboard");
//		m_cuttingBoard->SetPosition(objData.position);
//		m_cuttingBoard->SetRotation(objData.rotation);
//		m_cuttingBoard->SetScale(objData.scale);
//	}
//
//	//���􂢏�B
//	if (objData.EqualObjectName(L"kitchen") == true)
//	{
//		m_kitchen = NewGO<Kitchen>(0, "kitchen");
//		m_kitchen->SetPosition(objData.position);
//		m_kitchen->SetRotation(objData.rotation);
//		m_kitchen->SetScale(objData.scale);
//	}
//
//	//�󂯓n�����B
//	if (objData.EqualObjectName(L"derivery") == true)
//	{
//		m_delivery = NewGO<Delivery>(0, "delivery");
//		m_delivery->SetPosition(objData.position);
//		m_delivery->SetRotation(objData.rotation);
//		m_delivery->SetScale(objData.scale);
//	}
//
//	//�g�}�g�̔��B
//	if (objData.EqualObjectName(L"TomatoBox") == true)
//	{
//		m_tomatoBox = NewGO<TomatoBox>(0, "tomatobox");
//		m_tomatoBox->SetPosition(objData.position);
//		m_tomatoBox->SetRotation(objData.rotation);
//		m_tomatoBox->SetScale(objData.scale);
//	}
//
//	//�ʂ˂��̔��B
//	if (objData.EqualObjectName(L"OnionBox") == true)
//	{
//		m_onionBox = NewGO<OnionBox>(0, "onionbox");
//		m_onionBox->SetPosition(objData.position);
//		m_onionBox->SetRotation(objData.rotation);
//		m_onionBox->SetScale(objData.scale);
//	}
//}

void StageBase::Update()
{

}