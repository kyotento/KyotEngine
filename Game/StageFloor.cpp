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

//�X�e�[�W�𐶐�����B
void StageFloor::NewSelectFloor(int stageNum)
{

	//todo �X�e�[�W�������炱���ɂ������Ă����B
	if (stageNum == 1) {
		m_skinModelRender->Init(L"Assets/modelData/Stage1Floor.cmo");
	}

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	m_physicsStaticObject.CreateMeshObject(m_skinModelRender->GetSkinModel(), m_position, m_rotation);
}
