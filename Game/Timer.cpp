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

	return true;
}

void Timer::Update()
{
	m_timer -= gametime().GetFrameDeltaTime();				//時間経過。

}
