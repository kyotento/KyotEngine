#include "stdafx.h"
#include "StageFloor.h"


StageFloor::StageFloor()
{
}


StageFloor::~StageFloor()
{
}

bool StageFloor::Start()
{

	return true;
}

//ステージを生成する。
void StageFloor::NewSelectFloor(int stageNum)
{

	//todo ステージ増えたらここについかしていく。
	if (stageNum == 1) {
		m_skinModelRender->Init(L"Assets/modelData/Stage1Floor.cmo");
	}

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	m_physicsStaticObject.CreateMeshObject(m_skinModelRender->GetSkinModel(), m_position, m_rotation);
}
