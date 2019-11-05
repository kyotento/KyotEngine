#include "stdafx.h"
#include "Stage_1.h"


Stage_1::Stage_1()
{
}

Stage_1::~Stage_1()
{
}

bool Stage_1::Start()
{

	m_level.Init(L"Assets/level/stage_1.tkl", [&](LevelObjectData& objData)
		{
			
		//	LevelGeneration(objData);

			//�n�ʁB
			if (objData.EqualObjectName(L"kari_floor") == true)
			{
				return false;
			}

			//���B
			if (objData.EqualObjectName(L"Desk") == true)
			{
				m_desk = NewGO<Desk>(0, "desk");
				m_desk->SetPosition(objData.position);
				m_desk->SetRotation(objData.rotation);
				m_desk->SetScale(objData.scale);
			}

			//���M�u���B
			if (objData.EqualObjectName(L"DishHold") == true)
			{
				m_dishHold = NewGO<DishHold>(0, "dishhold");
				m_dishHold->SetPosition(objData.position);
				m_dishHold->SetRotation(objData.rotation);
				m_dishHold->SetScale(objData.scale);
			}

			//�K�X�R�����B
			if (objData.EqualObjectName(L"gas_stove") == true)
			{
				m_gasStove = NewGO<GasStove>(0, "gasstove");
				m_gasStove->SetPosition(objData.position);
				m_gasStove->SetRotation(objData.rotation);
				m_gasStove->SetScale(objData.scale);

				//����B
				m_pot = NewGO<Pot>(0, "pot");		//���New�B
				CVector3 m_position;				//��̉��l�B
				m_position = objData.position;		//�K�X�R�����̍��W�����B
				m_position.y += 80.f;				//�����W�̂ݏグ�Ă��B
				m_pot->SetPosition(m_position);		//��̍��W�w��B

				m_gasStove->PutThings(m_pot);		//�K�X�R�����̏�ɓ��u�������B

				m_gasStove->SetState(1);			//�K�X�R�����̃X�e�[�g�ύX�B

			}

			//�S�~���B
			if (objData.EqualObjectName(L"DustBox") == true)
			{
				m_dustbox = NewGO<DustBox>(0, "dustbox");
				m_dustbox->SetPosition(objData.position);
				m_dustbox->SetRotation(objData.rotation);
				m_dustbox->SetScale(objData.scale);

			}

			//�܂Ȕt�����B
			if (objData.EqualObjectName(L"cutting_desk") == true)
			{
				m_cuttingDesk = NewGO<CuttingDesk>(0, "cuttingdesk");
				m_cuttingDesk->SetPosition(objData.position);
				m_cuttingDesk->SetRotation(objData.rotation);
				m_cuttingDesk->SetScale(objData.scale);
			}

			//���􂢏�B
			if (objData.EqualObjectName(L"kitchen") == true)
			{
				m_kitchen = NewGO<Kitchen>(0, "kitchen");
				m_kitchen->SetPosition(objData.position);
				m_kitchen->SetRotation(objData.rotation);
				m_kitchen->SetScale(objData.scale);
			}

			//�󂯓n�����B
			if (objData.EqualObjectName(L"derivery") == true)
			{
				m_delivery = NewGO<Delivery>(0, "delivery");
				m_delivery->SetPosition(objData.position);
				m_delivery->SetRotation(objData.rotation);
				m_delivery->SetScale(objData.scale);
			}

			//�g�}�g�̔��B
			if (objData.EqualObjectName(L"TomatoBox") == true)
			{
				m_tomatoBox = NewGO<TomatoBox>(0, "tomatobox");
				m_tomatoBox->SetPosition(objData.position);
				m_tomatoBox->SetRotation(objData.rotation);
				m_tomatoBox->SetScale(objData.scale);
			}

			//�ʂ˂��̔��B
			if (objData.EqualObjectName(L"OnionBox") == true)
			{
				m_onionBox = NewGO<OnionBox>(0, "onionbox");
				m_onionBox->SetPosition(objData.position);
				m_onionBox->SetRotation(objData.rotation);
				m_onionBox->SetScale(objData.scale);
			}

			//��B
			if (objData.EqualObjectName(L"Knife") == true)
			{
				m_knife = NewGO<Knife>(0, "knife");
				m_knife->SetPosition(objData.position);
				m_knife->SetRotation(objData.rotation);
				m_knife->SetScale(objData.scale);
			}

			return true;

		});

	return true;
}

void Stage_1::Update()
{

}