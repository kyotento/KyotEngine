#include "stdafx.h"
#include "StageSelect.h"


StageSelect::StageSelect()
{
}


StageSelect::~StageSelect()
{
	DeleteGOs("flag");
}


bool StageSelect::Start()
{
	//���x��
	m_level.Init(L"Assets/level/StageSelect.tkl", [&](LevelObjectData& objData)
	{
		//�n�ʁB
		if (objData.EqualObjectName(L"floor") == true)
		{
			return false;
		}

		//���B
		if (objData.EqualObjectName(L"Flag") == true)
		{
			m_flag = NewGO<Flag>(0, "flag");
			m_flag->SetPosition(objData.position);
			m_flag->SetScale(objData.scale);
			m_flag->SetRotation(objData.rotation);
		}

		//�o�X�B
		if (objData.EqualObjectName(L"bus") == true)
		{
			m_bus = NewGO<Bus>(0, "bus");
			m_bus->SetPosition(objData.position);
			m_bus->SetScale(objData.scale);
			m_bus->SetRotation(objData.rotation);
		}

		//���B
		if (objData.EqualObjectName(L"bridge") == true)
		{
			m_bridge = NewGO<Bridge>(0, "bridge");
			m_bridge->SetPosition(objData.position);
			m_bridge->SetScale(objData.scale);
			m_bridge->SetRotation(objData.rotation);
		}

		//��B
		if (objData.EqualObjectName(L"river") == true)
		{
			m_river = NewGO<River>(0, "river");
			m_river->SetPositon(objData.position);
			m_river->SetScale(objData.scale);
			m_river->SetRotation(objData.rotation);
		}

		return true;
	});

	return true;
}

void StageSelect::Update()
{

}