#include "stdafx.h"
#include "Title.h"


Title::Title()
{
}


Title::~Title()
{
	
	DeleteGO(m_spriteRender);
}

bool Title::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");
	m_spriteRender->Init(L"Assets/sprite/Title.dds", 720, 1280 , false);
	m_spriteRender->SetPosition(m_position);
	
	return true;
}


void Title::Update()
{

}