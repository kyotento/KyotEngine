#include "stdafx.h"
#include "MapChip.h"
#include "Level.h"

MapChip::MapChip(const LevelObjectData& objData)
{
	wchar_t filePath[256];
	swprintf_s(filePath, L"Assets/modelData/%s.cmo", objData.name);
	//m_model.Init(filePath, m_psmain, m_vsmain);
	//m_model.UpdateWorldMatrix(objData.position, objData.rotation, CVector3::One());

	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRender->Init(filePath);
	m_skinModelRender->Update(/*objData.position, objData.rotation, objData.scale*/);
	m_skinModelRender->SetPosition(objData.position);
	m_skinModelRender->SetScale(objData.scale);
	m_skinModelRender->SetRotation(objData.rotation);

	//静的物理オブジェクトをメッシュコライダーから作成する。
	m_physicsStaticObject.CreateMeshObject(/*m_model, */m_skinModelRender->GetSkinModel() ,objData.position, objData.rotation);
}

void MapChip::Draw()
{
	m_model.Draw(enRenderMode_Normal,g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());

}