#include "stdafx.h"
#include "SpriteRender.h"


SpriteRender::SpriteRender()
{
}


SpriteRender::~SpriteRender()
{
}

void SpriteRender::Init(const wchar_t* textureFilePath, float w, float h, bool isDraw3D )
{
	m_Draw3D = isDraw3D;
	m_sprite.Init(textureFilePath, w, h);
	m_w = w;
	m_h = h;
	
}

void SpriteRender::PostRender()
{
	//画像の更新処理。	
	m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);

	if (m_Draw3D == true)			//3D空間上に描画するとき。
	{
		/*Camera::EnUpdateProjMatrixFunc*/ m_projMatrixFunc = Camera::enUpdateProjMatrixFunc_Perspective;
		/*m_camera.SetUpdateCameraMatrix(false);*/

	}

	if (m_Draw3D == false)			//2D空間上に描画するとき。
	{
		/*Camera::EnUpdateProjMatrixFunc*/ m_projMatrixFunc = Camera::enUpdateProjMatrixFunc_Ortho;
/*
		camera2d.m_UpdateCameraMatrix*/
		camera2d.SetUpdateCameraMatrix(true);

	}

	if (m_projMatrixFunc == Camera::enUpdateProjMatrixFunc_Perspective)
	{
		m_sprite.Draw(&g_camera3D);
	}

	if (m_projMatrixFunc == Camera::enUpdateProjMatrixFunc_Ortho)
	{
		m_sprite.Draw(&camera2d);
	}
}
