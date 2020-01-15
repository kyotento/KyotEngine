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

	return true;
}

void Score::Update()
{

}