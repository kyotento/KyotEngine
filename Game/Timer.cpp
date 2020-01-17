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
	m_startCountDown = FindGO<StartCountdown>("startcountdown");			//StartCountDown�̃C���X�^���X���擾�B

	m_spriteRender = NewGO<SpriteRender>(0, "sprite");
	m_spriteRender->Init(L"Assets/sprite/Timer.dds", spriteScale, spriteScale);			//�������B
	m_position2D.x = x;														//X���W���w��B
	m_position2D.y = y;														//Y���W���w��B
	m_spriteRender->SetPosition(m_position2D);								//���W���w��B

	m_fontPosition.x = m_position2D.x -= 90.f;			//�t�H���g��X���W���w��B
	m_fontPosition.y = m_position2D.y += 30.f;			//�t�H���g��Y���W���w��B

	UnitChange();			//00:00�ƕ\�����邽�߂̌v�Z���s���B

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
	if (m_startCountDown->GetGameStartFlag()) {					////�Q�[���X�V�������J�n���Ă�����B
		m_timer -= gametime().GetFrameDeltaTime();				//���Ԍo�߁B
		UnitChange();											//00:00�ƕ\�����邽�߂̌v�Z�B

		if (m_timer <= 0.f) {			//���Ԑ����������Ƃ��B
			m_startCountDown->SetGameStartFlag(false);			//�Q�[���̍X�V�������I������B
			m_gameOver = NewGO<GameOver>(0, "gameover");		//�Q�[�����I������B
		}
	}
}

void Timer::AfterFontRender()
{
	m_font.Begin();
	wchar_t text[64];
	swprintf_s(text, L"%01d:%02d", m_minute, m_second);
	m_font.Draw(text, m_fontPosition,m_fontColor,0.0f,m_fontScale);
	m_font.End();

}