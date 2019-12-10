#include "stdafx.h"
#include "Gauge.h"


Gauge::Gauge()
{
}


Gauge::~Gauge()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_skinModelRenderGauge);
}

bool Gauge::Start()
{
	////ゲージ基盤。
	//m_spriteRender = NewGO<SpriteRender>(3, "sprite");
	//m_spriteRender->Init(L"Assets/sprite/gauge_sheet.dds", 72, 18, true);
	//m_spriteRender->SetPosition(m_position);
	//m_spriteRender->SetScale({1.f,1.f,1.f});
	//m_spriteRender->SetPivot(m_pivot);

	////ゲージ。
	//m_spriteRenderGauge = NewGO<SpriteRender>(2, "sprite");
	//m_spriteRenderGauge->Init(L"Assets/sprite/gauge.dds", 66, 16, true);
	//m_spriteRenderGauge->SetPosition(m_position);
	//m_spriteRenderGauge->SetScale({ m_x,1.f,1.f });
	//m_spriteRenderGauge->SetPivot(m_pivot);

	//ゲージの基盤。
	m_skinModelRender = NewGO<SkinModelRender>(2, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/2D/Gauge/GaugeSheet.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale({ 1.f,1.f,1.f });

	//ゲージ。
	m_skinModelRenderGauge = NewGO<SkinModelRender>(1, "skinModel");
	m_skinModelRenderGauge->Init(L"Assets/modelData/2D/Gauge/Gauge.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
	m_skinModelRenderGauge->SetPosition(m_position);
	m_skinModelRenderGauge->SetScale({ m_x, 1.f, 1.f });

	return true;
}

void Gauge::Expansion(float a)
{
	//todo 絶　切った時に拡大する。Xが１になると切られた状態にする。0.2秒に一回切る。
	float ExpensionSpeed;
	ExpensionSpeed = 1 / (a * 60.f);

	if (m_skinModelRenderGauge != nullptr) {
		if (m_x <= 1.f)		//拡大率が１以下のとき。
		{
			m_x += ExpensionSpeed;	//拡大する。
			m_skinModelRenderGauge->SetScale({ m_x,1.f,1.f });		//拡大を更新。
		}
	}
}

void Gauge::Update()
{
//	m_skinModelRender->SetPosition(m_position);			//座標を更新。
	m_skinModelRenderGauge->SetPosition(m_position);	//ゲージの座標を更新。

	if (m_gaugeMax == false && m_x >= 1.f)
	{
		m_gaugeMax = true;
	}

}