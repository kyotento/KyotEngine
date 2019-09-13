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
	m_game = FindGO<Game>("game");
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");
	m_spriteRender->Init(L"Assets/sprite/Title.dds", 720, 1280 , false);
	m_spriteRender->SetPosition(m_position);
	
	return true;
}


void Title::Update()
{

	if (g_pad[0].IsPress(enButtonB))
	{
		m_game->SetTitleDeleteFlag(true);
		DeleteGO(this);
	}
}