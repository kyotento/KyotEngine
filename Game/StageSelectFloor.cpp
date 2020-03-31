#include "stdafx.h"
#include "StageSelectFloor.h"


StageSelectFloor::StageSelectFloor()
{
}


StageSelectFloor::~StageSelectFloor()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_skinModelRenderCollision);
}


bool StageSelectFloor::Start()
{
	//モデルのロード。
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodelrender");
	m_skinModelRender->Init(L"Assets/modelData/floor.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);
	m_physicsStaticObject.CreateMeshObject(m_skinModelRender->GetSkinModel(), m_position, m_rotation);		//当たり判定作成。

	//川に落ちないための当たり判定。
	m_skinModelRenderCollision = NewGO<SkinModelRender>(0, "skinmodelrender");
	m_skinModelRenderCollision->Init(L"Assets/modelData/StageSelect/stageSelectCollision.cmo");
	m_skinModelRenderCollision->SetPosition(m_position);
	m_skinModelRenderCollision->SetScale(m_scale);
	m_skinModelRenderCollision->SetRotation(m_rotation);
	m_physicsStaticObjectCollision.CreateMeshObject(m_skinModelRenderCollision->GetSkinModel(), m_position, m_rotation);
	DeleteGO(m_skinModelRenderCollision);


	return true;
}

void StageSelectFloor::Update()
{

}