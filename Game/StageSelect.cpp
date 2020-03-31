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
			m_stageSelectFloor = NewGO<StageSelectFloor>(0, "stageselectfloor");
			m_stageSelectFloor->SetPosition(objData.position);
			m_stageSelectFloor->SetScale(objData.scale);
			m_stageSelectFloor->SetRotation(objData.rotation);
		}

		//ステージ1用の旗。
		if (objData.EqualObjectName(L"FlagStage1") == true)
		{
			m_flag = NewGO<Flag>(0, "flag1");
			m_flag->SetPosition(objData.position);
			m_flag->SetScale(objData.scale);
			m_flag->SetRotation(objData.rotation);
		}

		//ステージ2用の旗。
		if (objData.EqualObjectName(L"FlagStage2") == true)
		{
			m_flag = NewGO<Flag>(0, "flag2");
			m_flag->SetPosition(objData.position);
			m_flag->SetScale(objData.scale);
			m_flag->SetRotation(objData.rotation);
		}

		//ステージ3用の旗。
		if (objData.EqualObjectName(L"FlagStage3") == true)
		{
			m_flag = NewGO<Flag>(0, "flag3");
			m_flag->SetPosition(objData.position);
			m_flag->SetScale(objData.scale);
			m_flag->SetRotation(objData.rotation);
		}

		//バス。
		if (objData.EqualObjectName(L"bus") == true)
		{
			m_bus = NewGO<Bus>(0, "bus");
			m_bus->SetPosition(objData.position);
			m_bus->SetScale(objData.scale);
			m_bus->SetRotation(objData.rotation);
		}

		//橋。
		if (objData.EqualObjectName(L"bridge") == true)
		{
			m_bridge = NewGO<Bridge>(0, "bridge");
			m_bridge->SetPosition(objData.position);
			m_bridge->SetScale(objData.scale);
			m_bridge->SetRotation(objData.rotation);
		}

		//川。
		if (objData.EqualObjectName(L"river") == true)
		{
			m_river = NewGO<River>(0, "river");
			m_river->SetPositon(objData.position);
			m_river->SetScale(objData.scale);
			m_river->SetRotation(objData.rotation);
		}

		return true;
	});

	//ステージの詳細画像生成処理用クラスを生成。
	m_stageSelectDetailed = NewGO<StageSelectDetailed>(0, "stageselectdetailed");

	return true;
}

void StageSelect::Update()
{

}