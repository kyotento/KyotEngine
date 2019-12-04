#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B

Camera camera2d;		//2D�J�����B

void Camera::Update()
{

	//�r���[�s����v�Z�B
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);

	//�˖@���e�B
	if (m_UpdateCameraMatrix == enUpdateProjMatrixFunc_Perspective) {

		//�v���W�F�N�V�����s����v�Z�B
		m_projMatrix.MakeProjectionMatrix(
			m_viewAngle,					//��p�B
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//�A�X�y�N�g��B
			m_near,
			m_far
		);
	}

	//���s���e�B
	if (m_UpdateCameraMatrix == enUpdateProjMatrixFunc_Ortho)
	{
		m_projMatrix.MakeOrthoProjectionMatrix(
			FRAME_BUFFER_W,				//��ʂ̕��B
			FRAME_BUFFER_H,				//��ʂ̍����B
			m_near,						//�ߕ��ʁB
			m_far						//�����ʁB
		);

	}

}