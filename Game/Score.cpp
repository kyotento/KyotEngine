#include "stdafx.h"
#include "Score.h"

namespace {
 	const float x = -565.f;			//�摜��X���W�B
	const float y = -285.f;			//�摜��Y���W�B

	const float spriteScale = 150.f;	//�摜�̃X�P�[���B
}

Score::Score()
{
}

Score::~Score()
{
	DeleteGO(m_spriteRender);		//�X�L�����f���������B
}

bool Score::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");
	m_spriteRender->Init(L"Assets/sprite/coin.dds", spriteScale, spriteScale);			//�������B�@
	m_position2D.x = x;														//X���W���w��B
	m_position2D.y = y;														//Y���W���w��B
	m_spriteRender->SetPosition(m_position2D);								//���W��ݒ�B

	m_fontPosition.x = m_position2D.x -= 29.f;			//�t�H���g��X���W���w��B
	m_fontPosition.y = m_position2D.y += 45.f;			//�t�H���g��Y���W���w��B

	//todo�@���ۂ͑I�����ꂽ�X�e�[�W���ƂɈقȂ�B(�d�g�݂����)�B
	m_starOne = 150;
	m_starTwo = 300;
	m_starThree = 600;

	return true;
}

void Score::Update()
{
}

void Score::AfterFontRender()
{
	m_font.Begin();															//�`��J�n�B
	wchar_t text[64];														//�e�L�X�g�Ɏg���z��B
	swprintf_s(text, L"%01d", m_score);										//�e�L�X�g��ݒ�B
	m_font.Draw(text, m_fontPosition, m_fontColor, 0.0f, m_fontScale);		//�X�V�����B
	m_font.End();															//�`��I���B
}