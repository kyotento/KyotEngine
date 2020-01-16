#include "stdafx.h"
#include "Timer.h"

namespace {
	float x = 565.f;		//X座標。
	float y = -285.f;		//Y座標。

	float spriteScale = 150.f;		//画像のサイズ。
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
	m_spriteRender->Init(L"Assets/sprite/Timer.dds", spriteScale, spriteScale);			//初期化。
	m_position2D.x = x;														//X座標を指定。
	m_position2D.y = y;														//Y座標を指定。
	m_spriteRender->SetPosition(m_position2D);								//座標を指定。

//	m_fontRender = NewGO<FontRender>(0, "fontrender");				//フォントクラスを生成。
//	UnitChange();
////	std::printf("%d:%d", m_minute, m_second);
//	wchar_t a[256];
//	a[256] = ("%d:%d",m_minute,m_second);
//	m_fontRender->SetText(&a[256]);									//テキストを設定。
////	printf("%d:%d",m_minute,m_second);
	m_fontPosition.x = m_position2D.x -= 70.f; 
	m_fontPosition.y = m_position2D.y += 20.f;
//	m_fontRender->SetPosition(m_fontPosition);						//座標を指定。
//	m_fontRender->SetColor(m_fontColor);
//	m_fontRender->SetScale(m_fontScale);

	return true;
}

//00:00と表示するための計算。
void Timer::UnitChange()
{
	m_minute = m_timer / 60.f;				//分の計算。
	m_second = m_timer - 60 * m_minute;		//秒の計算。
}

void Timer::Update()
{
	m_timer -= gametime().GetFrameDeltaTime();				//時間経過。
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