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
	m_game = FindGO<Game>("game");			//Game�N���X�������B
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");						//�摜�`��N���X�𐶐��B
	m_spriteRender->Init(L"Assets/sprite/Title.dds", 1280, 720 , false);	//�������B
	m_spriteRender->SetPosition(m_position);								//���W�X�V�B
	
	return true;
}

void Title::Update()
{
	if (g_pad[0].IsPress(enButtonB))			//1P���{�^�����������Ƃ��B
	{
		m_game->SetTitleDeleteFlag(true);		//Delete�t���O��Ԃ��B
		DeleteGO(this);							//�N���X�������B
	}
}