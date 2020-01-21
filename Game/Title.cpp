#include "stdafx.h"
#include "Title.h"

namespace {
	CVector2 fontPos = { 100.f,-200.f};				//�t�H���g�̍��W�B
	CVector2 fontPos2 = { 100.f,-300.f};			//�t�H���g�̍��W�B
}

Title::Title()
{
}

Title::~Title()
{
	DeleteGO(m_spriteRender);
	DeleteGO(se);
	DeleteGO(m_fontRender);
	DeleteGO(m_fontRender2);
}

bool Title::Start()
{
	m_game = FindGO<Game>("game");			//Game�N���X�������B
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");						//�摜�`��N���X�𐶐��B
	m_spriteRender->Init(L"Assets/sprite/Title.dds", 1280, 720 , false);	//�������B
	m_spriteRender->SetPosition(m_position);								//���W�X�V�B

	//�t�H���g�𐶐��B
	m_fontRender = NewGO<FontRender>(0, "fontrender");			//�t�H���g�N���X�B
	m_fontRender->SetText(L"B�ڂ���������Ă�");				//�e�L�X�g�̎w��B
	m_fontRender->SetPosition(fontPos);							//���W���w��B
		
	m_fontRender2 = NewGO<FontRender>(0, "fontrender");			//�t�H���g�N���X�B
	m_fontRender2->SetText(L"BGM::MusMus");						//�e�L�X�g�̎w��B
	m_fontRender2->SetPosition(fontPos2);						//���W�̎w��B
	
	//BGM�B
	se = NewGO<Sound>(0, "sound");								//�T�E���h�N���X�B
	se->Init(L"Assets/sound/BGM/title_overcooked.wav",true);	//�������B
	se->Play();													//�Đ��B

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