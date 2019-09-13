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

	m_level.Init(L"stage_1.tkl", [&](LevelObjectData& objData)
		{
			return true;
		});

	return true;
}

void Stage_1::Update()
{

}
