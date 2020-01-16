#include "stdafx.h"
#include "Score.h"

namespace {
	float x = -565.f;			//�摜��X���W�B
	float y = -285.f;			//�摜��Y���W�B

	float spriteScale = 150.f;
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

	m_fontPosition.x = m_position2D.x -= 35.f;
	m_fontPosition.y = m_position2D.y += 20.f;

	return true;
}

void Score::Update()
{
	//todo ���B
	m_score += 1;
}

void Score::AfterFontRender()
{
	m_font.Begin();
	wchar_t text[64];
	swprintf_s(text, L"%01d", m_score);
	m_font.Draw(text, m_fontPosition, m_fontColor, 0.0f, m_fontScale);
	m_font.End();

}