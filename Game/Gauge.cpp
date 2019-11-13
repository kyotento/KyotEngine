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
	//ゲージ基盤。
	m_spriteRender = NewGO<SpriteRender>(3, "sprite");
	m_spriteRender->Init(L"Assets/sprite/gauge_sheet.dds", 18, 72, true);
	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetScale({1.f,1.f,1.f});
	m_spriteRender->SetPivot(m_pivot);

	//ゲージ。
	m_spriteRenderGauge = NewGO<SpriteRender>(2, "sprite");
	m_spriteRenderGauge->Init(L"Assets/sprite/gauge.dds", 16, 66, true);
	m_spriteRenderGauge->SetPosition(m_position);
	m_spriteRenderGauge->SetScale({ m_x,1.f,1.f });
	m_spriteRenderGauge->SetPivot(m_pivot);


	return true;
}

void Gauge::Expansion()
{
	//todo 絶　切った時に拡大する。Xが１になると切られた状態にする。0.2秒に一回切る。
	if (m_spriteRenderGauge != nullptr) {
		if (m_x <= 1.f)		//拡大率が１以下のとき。
		{
			m_x += 0.2f;	//拡大する。
			m_spriteRenderGauge->SetScale({ m_x,1.f,1.f });		//拡大を更新。
		}
	}
}

void Gauge::Update()
{
	m_spriteRender->SetPosition(m_position);			//座標を更新。
	m_spriteRenderGauge->SetPosition(m_position);		//ゲージの座標を更新。
	m_spriteRenderGauge->SetScale(m_scaleGauge);		//ゲージのスケールを更新。

}