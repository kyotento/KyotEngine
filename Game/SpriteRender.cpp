#include "stdafx.h"
#include "Sprite.h"
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

void SpriteRender::Update()
{
	m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
	if (m_Draw3D == false)
	{
		Camera::EnUpdateProjMatrixFunc m_projMatrixFunc = Camera::enUpdateProjMatrixFunc_Ortho;

	}

	if (m_Draw3D == true)
	{
		Camera::EnUpdateProjMatrixFunc m_projMatrixFunc = Camera::enUpdateProjMatrixFunc_Perspective;

	}

	if (m_projMatrixFunc == Camera::enUpdateProjMatrixFunc_Perspective)
		m_sprite.Draw();

	if (m_projMatrixFunc == Camera::enUpdateProjMatrixFunc_Ortho)
		m_sprite.Draw();

}
