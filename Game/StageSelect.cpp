#include "stdafx.h"
#include "StageSelect.h"


StageSelect::StageSelect()
{
}


StageSelect::~StageSelect()
{
	DeleteGO(m_stageSelectDetailed);
	DeleteGO(m_stageSelectFloor);
	for(int i = 0; i <= 2; i++) {
		DeleteGO(m_flag[i]);
	}
	DeleteGO(m_bus);
	DeleteGOs("bridge");
	DeleteGO(m_river);
	DeleteGO(m_spriteRender);
	DeleteGO(m_sound);
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
			m_flag[0] = NewGO<Flag>(0, "flag1");
			m_flag[0]->SetPosition(objData.position);
			m_flag[0]->SetScale(objData.scale);
			m_flag[0]->SetRotation(objData.rotation);
		}

		//ステージ2用の旗。
		if (objData.EqualObjectName(L"FlagStage2") == true)
		{
			m_flag[1] = NewGO<Flag>(0, "flag2");
			m_flag[1]->SetPosition(objData.position);
			m_flag[1]->SetScale(objData.scale);
			m_flag[1]->SetRotation(objData.rotation);
		}

		//ステージ3用の旗。
		if (objData.EqualObjectName(L"FlagStage3") == true)
		{
			m_flag[2] = NewGO<Flag>(0, "flag3");
			m_flag[2]->SetPosition(objData.position);
			m_flag[2]->SetScale(objData.scale);
			m_flag[2]->SetRotation(objData.rotation);
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

	//ステージセレクト画像描画処理。
	m_spriteRender = NewGO<SpriteRender>(0, "spriterender");
	m_spriteRender->Init(L"Assets/sprite/StageSelect.dds", 1080, 720);
	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetScale(m_scale);
	m_spriteRender->SetRotation(m_rotation);

	//BGM。
	m_sound = NewGO<Sound>(0, "sound");
	m_sound->Init(L"Assets/sound/BGM/StageSelectBGM.wav", true);
	m_sound->Play();


	//ステージの詳細画像生成処理用クラスを生成。
	m_stageSelectDetailed = NewGO<StageSelectDetailed>(0, "stageselectdetailed");

	return true;
}

void StageSelect::Update()
{

}