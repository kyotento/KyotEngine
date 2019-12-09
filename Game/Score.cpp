#include "stdafx.h"
#include "Score.h"

namespace {
	float x = -540.f;			//�摜��X���W�B
	float y = -260.f;			//�摜��Y���W�B
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
	m_spriteRender->Init(L"Assets/sprite/coin.dds", 200.f, 200.f);			//�������B�@
	m_position2D.x = x;														//X���W���w��B
	m_position2D.y = y;														//Y���W���w��B
	m_spriteRender->SetPosition(m_position2D);								//���W��ݒ�B

	return true;
}

void Score::Update()
{

}