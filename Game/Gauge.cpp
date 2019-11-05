#include "stdafx.h"
#include "Gauge.h"


Gauge::Gauge()
{
}


Gauge::~Gauge()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_spriteRenderGauge);
}

bool Gauge::Start()
{
	//�Q�[�W��ՁB
	m_spriteRender = NewGO<SpriteRender>(3, "sprite");
	m_spriteRender->Init(L"Assets/sprite/gauge_sheet.dds", 18, 72, true);
	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetScale({1.f,1.f,1.f});
	m_spriteRender->SetPivot(m_pivot);

	//�Q�[�W�B
	m_spriteRenderGauge = NewGO<SpriteRender>(2, "sprite");
	m_spriteRenderGauge->Init(L"Assets/sprite/gauge.dds", 16, 66, true);
	m_spriteRenderGauge->SetPosition(m_position);
	m_spriteRenderGauge->SetScale({ m_x,1.f,1.f });
	m_spriteRenderGauge->SetPivot(m_pivot);


	return true;
}

void Gauge::Expansion()
{
	//todo ��@�؂������Ɋg�傷��BX���P�ɂȂ�Ɛ؂�ꂽ��Ԃɂ���B0.2�b�Ɉ��؂�B
	if (m_x <= 1.f)
	{
		m_x += 0.2f;
		m_spriteRenderGauge->SetScale({ m_x,1.f,1.f });
	}

}

void Gauge::Update()
{
	m_spriteRender->SetPosition(m_position);

}