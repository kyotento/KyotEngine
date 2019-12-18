#include "stdafx.h"
#include "OrderSheet.h"


OrderSheet::OrderSheet()
{
}

OrderSheet::~OrderSheet()
{
	DeleteGO(m_spriteRenderSheetNo1);
	DeleteGO(m_spriteRenderSheetNo2);
}

bool OrderSheet::Start()
{
	m_spriteRenderSheetNo1 = NewGO<SpriteRender>(0, "sprite");
	m_spriteRenderSheetNo1->Init(L"Assets/sprite/Food_Sheet.dds", 150.f, 80.f);
	m_spriteRenderSheetNo1->SetPosition(m_position);
	m_spriteRenderSheetNo1->SetRotation(m_rotation);

	m_spriteRenderSheetNo2 = NewGO<SpriteRender>(0, "sprite");
	m_spriteRenderSheetNo2->Init(L"Assets/sprite/Food_Sheet2.dds", 150.f, 80.f);
	m_spriteRenderSheetNo2->SetPosition(m_position);
	m_spriteRenderSheetNo2->SetRotation(m_rotation);

	return true;
}

void OrderSheet::Update()
{
	m_spriteRenderSheetNo1->SetPosition(m_position);
	m_spriteRenderSheetNo2->SetPosition(m_position);

}
