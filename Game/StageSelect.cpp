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
	//レベル
	m_level.Init(L"Assets/level/StageSelect.tkl", [&](LevelObjectData& objData)
	{
		//地面。
		if (objData.EqualObjectName(L"floor") == true)
		{
			return false;
		}

		//旗。
		if (objData.EqualObjectName(L"Flag") == true)
		{
			m_flag = NewGO<Flag>(0, "flag");
			m_flag->SetPosition(objData.position);
			m_flag->SetScale(objData.scale);
			m_flag->SetRotation(objData.rotation);
		}

		return true;
	});

	return true;
}

void StageSelect::Update()
{

}