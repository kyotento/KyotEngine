#include "stdafx.h"
#include "Timer.h"

namespace {
	float x = 540.f;
	float y = -260.f;
}

Timer::Timer()
{
}


Timer::~Timer()
{
}

bool Timer::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");
	m_spriteRender->Init(L"Assets/sprite/Timer.dds", 200.f, 200.f);			//�������B
	m_position2D.x = x;														//X���W���w��B
	m_position2D.y = y;														//Y���W���w��B
	m_spriteRender->SetPosition(m_position2D);								//���W���w��B

	return true;
}

void Timer::Update()
{
	/*m_timer -= 1.f;*/

}
