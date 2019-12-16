#include "stdafx.h"
#include "Gauge.h"

//#define GAUGE_TEST

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

#ifdef GAUGE_TEST

	////ゲージの基盤。
	m_skinModelRender = NewGO<SkinModelRender>(1, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/2D/Gauge/GaugeSheet.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale({ 1.f,1.f,1.f });

#endif
	//ゲージ。
	m_skinModelRenderGauge = NewGO<SkinModelRender>(2, "skinModel");
	m_skinModelRenderGauge->Init(L"Assets/modelData/2D/Gauge/Gauge.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
	m_skinModelRenderGauge->SetPosition(m_position);
	m_skinModelRenderGauge->SetScale({ m_x, 1.f, 1.f });

	return true;
}

//ゲージを拡大する処理。
void Gauge::Expansion(float time)
{
	float ExpensionSpeed;
	ExpensionSpeed = 1 / (time * 60.f);		//引数秒で拡大率を１にするための計算。

	if (m_skinModelRenderGauge != nullptr) {
		if (m_x <= 1.f)		//拡大率が１以下のとき。
		{
			m_x += ExpensionSpeed;	//拡大する。
			m_skinModelRenderGauge->SetScale({ m_x,1.f,1.f });		//拡大を更新。
		}
	}
}

//ゲージを拡大する処理。
void Gauge::Magnification(float time, float numberOfTimes)
{
	if (m_x < 1.f) {								//拡大率が１以下のとき。
		float x = 1 / numberOfTimes;				//拡大率を計算。
		m_expansionTimer += 1.f / 60.f;				//タイマーを計算する。
		float TimeInterval = time / numberOfTimes;	//拡大時間間隔を計算。

		if (m_expansionTimer >= TimeInterval) {		//タイマーが拡大時間間隔以上のとき。
			m_x += x;								//拡大率を加算。
			m_expansionTimer = 0.f;					//タイマーをリセット。
			m_skinModelRenderGauge->SetScale({ m_x,1.f,1.f });		//スケールを更新。
		}
	}
	else
	{			//拡大率が１を超えた時。
		m_gaugeMax = true;		//ゲージが最大になったのでフラグを返す。
	}
}

void Gauge::Update()
{
	CVector3 oldPosition = m_position;
#ifdef GAUGE_TEST

	m_skinModelRender->SetPosition(m_position);			//座標を更新。

#endif
	m_skinModelRenderGauge->SetPosition(m_position);	//ゲージの座標を更新。

	if (m_gaugeMax == false && m_x >= 1.f)		
	{
		m_gaugeMax = true;
	}

	if (m_gaugeMax == true && m_x < 1.f)
	{
		m_gaugeMax = false;
	}

}