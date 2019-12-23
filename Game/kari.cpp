#include "stdafx.h"
#include "kari.h"


kari::kari()
{
}


kari::~kari()
{
}

bool kari::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "sp");
	m_spriteRender->Init(L"Assets/sprite/Food_Sheet3.dds",140.f, 80.f);
	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetScale(m_scale);

	return true;
}

void kari::Update()
{

}