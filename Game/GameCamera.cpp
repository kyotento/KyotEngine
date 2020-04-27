#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	g_camera3D.SetPosition(m_position);
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetNear(m_near);
	g_camera3D.SetFar(m_far);
	return true;
}

//カメラの視点、注視点をリセットする。
void GameCamera::CameraReset()
{
	m_position = { 0.0f, 900.0f, -600.0f };
	m_target = { 0.0f,0.0f,0.0f };
}

void GameCamera::Update()
{
	g_camera3D.SetPosition(m_position);
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetNear(m_near);
	g_camera3D.SetFar(m_far);

}