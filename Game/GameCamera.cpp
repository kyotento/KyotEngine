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

void GameCamera::Update()
{
	g_camera3D.SetPosition(m_position);
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetNear(m_near);
	g_camera3D.SetFar(m_far);

}