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

	return true;
}

void Timer::Update()
{
	m_timer -= gametime().GetFrameDeltaTime();				//���Ԍo�߁B

}
