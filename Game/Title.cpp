#include "stdafx.h"
#include "Title.h"


Title::Title()
{
}


Title::~Title()
{
}

bool Title::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");
	//m_spriteRender = Init(L"Asset/sprite/title.dds", 720, 1280 , false);
	
	return true;
}


void Title::Update()
{

}