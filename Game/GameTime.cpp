#include "stdafx.h"
#include "GameTime.h"


GameTime::GameTime()
{
}


GameTime::~GameTime()
{
}


void GameTime::PushFrameDeltaTime(float deltaTime)
{
	m_frameDeltaTimeQue.push_back(deltaTime);
	if (m_frameDeltaTimeQue.size() > 30.0f) {
		float totalTime = 0.0f;
		for (auto time : m_frameDeltaTimeQue) {
			totalTime += time;
		}
		//•½‹Ï’l‚ğ‚Æ‚éB
		m_frameDeltaTime = min(1.0f / m_fps, totalTime / m_frameDeltaTimeQue.size());
		m_frameDeltaTimeQue.pop_front();
	}
}