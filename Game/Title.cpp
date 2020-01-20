#include "stdafx.h"
#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
	DeleteGO(m_spriteRender);
	DeleteGO(se);
}

bool Title::Start()
{
	m_game = FindGO<Game>("game");			//Game�N���X�������B
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");						//�摜�`��N���X�𐶐��B
	m_spriteRender->Init(L"Assets/sprite/Title.dds", 1280, 720 , false);	//�������B
	m_spriteRender->SetPosition(m_position);								//���W�X�V�B
	
	//BGM�B
	se = NewGO<Sound>(0, "sound");
	se->Init(L"Assets/sound/BGM/title_overcooked.wav",true);
	se->Play();

	return true;
}

void Title::Update()
{
	if (g_pad[0].IsTrigger(enButtonB))			//1P���{�^�����������Ƃ��B
	{
		m_game->SetTitleDeleteFlag(true);		//Delete�t���O��Ԃ��B

		//���艹�B
		Sound* se2 = NewGO<Sound>(0, "sound");
		se2->Init(L"Assets/sound/soundEffect/decision3.wav", false);
		se2->Play();

		DeleteGO(this);							//�N���X�������B
	}
}