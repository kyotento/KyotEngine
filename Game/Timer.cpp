#include "stdafx.h"
#include "Timer.h"

namespace {
	float x = 565.f;		//X���W�B
	float y = -285.f;		//Y���W�B

	float spriteScale = 150.f;		//�摜�̃T�C�Y�B
}

Timer::Timer()
{
}


Timer::~Timer()
{
	DeleteGO(m_spriteRender);
}

bool Timer::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");
	m_spriteRender->Init(L"Assets/sprite/Timer.dds", spriteScale, spriteScale);			//�������B
	m_position2D.x = x;														//X���W���w��B
	m_position2D.y = y;														//Y���W���w��B
	m_spriteRender->SetPosition(m_position2D);								//���W���w��B

//	m_fontRender = NewGO<FontRender>(0, "fontrender");				//�t�H���g�N���X�𐶐��B
//	UnitChange();
////	std::printf("%d:%d", m_minute, m_second);
//	wchar_t a[256];
//	a[256] = ("%d:%d",m_minute,m_second);
//	m_fontRender->SetText(&a[256]);									//�e�L�X�g��ݒ�B
////	printf("%d:%d",m_minute,m_second);
	m_fontPosition.x = m_position2D.x -= 70.f; 
	m_fontPosition.y = m_position2D.y += 20.f;
//	m_fontRender->SetPosition(m_fontPosition);						//���W���w��B
//	m_fontRender->SetColor(m_fontColor);
//	m_fontRender->SetScale(m_fontScale);

	return true;
}

//00:00�ƕ\�����邽�߂̌v�Z�B
void Timer::UnitChange()
{
	m_minute = m_timer / 60.f;				//���̌v�Z�B
	m_second = m_timer - 60 * m_minute;		//�b�̌v�Z�B
}

void Timer::Update()
{
	m_timer -= gametime().GetFrameDeltaTime();				//���Ԍo�߁B
	UnitChange();
}

void Timer::AfterFontRender()
{
	m_font.Begin();
	wchar_t text[64];
	swprintf_s(text, L"%01d:%02d", m_minute, m_second);
	m_font.Draw(text, m_fontPosition,m_fontColor,0.0f,m_fontScale);
	m_font.End();

}