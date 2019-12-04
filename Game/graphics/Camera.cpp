#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。

Camera camera2d;		//2Dカメラ。

void Camera::Update()
{

	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);

	//射法投影。
	if (m_UpdateCameraMatrix == enUpdateProjMatrixFunc_Perspective) {

		//プロジェクション行列を計算。
		m_projMatrix.MakeProjectionMatrix(
			m_viewAngle,					//画角。
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比。
			m_near,
			m_far
		);
	}

	//平行投影。
	if (m_UpdateCameraMatrix == enUpdateProjMatrixFunc_Ortho)
	{
		m_projMatrix.MakeOrthoProjectionMatrix(
			FRAME_BUFFER_W,				//画面の幅。
			FRAME_BUFFER_H,				//画面の高さ。
			m_near,						//近平面。
			m_far						//遠平面。
		);

	}

}