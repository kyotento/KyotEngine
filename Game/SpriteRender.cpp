#include "stdafx.h"
#include "Sprite.h"
#include "SpriteRender.h"


SpriteRender::SpriteRender()
{
}


SpriteRender::~SpriteRender()
{
}

void SpriteRender::Init(const wchar_t* textureFilePath, float w, float h)
{
	m_sprite.Init(textureFilePath, w, h);
	m_w = w;
	m_h = h;
	
}
