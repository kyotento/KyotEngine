#include "stdafx.h"
#include "TimeLimitGauge.h"

namespace {
	float size_x = 110.f;
	float size_y = 20.f;
}

TimeLimitGauge::TimeLimitGauge()
{
}


TimeLimitGauge::~TimeLimitGauge()
{
	DeleteGO(m_spriteRender);
}

bool TimeLimitGauge::Start()
{
	m_spriteRender = NewGO<SpriteRender>(2, "sprite");
	m_spriteRender->Init(L"Assets/sprite/gauge_1.dds", size_x, size_y);
	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetScale(m_scale);
	m_spriteRender->SetPivot(m_pivot);

	return true;
}

//状態を変更する処理。
void TimeLimitGauge::StateChange()
{
	if (m_scale.x >= 0.66f) {							//ゲージのスケールが６６％以上のとき。
		m_gaugeState = en66Then;						//状態を変更する。
	}
	if (m_scale.x < 0.66f && m_scale.x >= 0.33f) {		//３３％以上のとき。
		m_gaugeState = en33Then;						//状態を変更する。
	}
	if (m_scale.x < 0.33f&& m_scale.x >= 0.1f) {		//１０％以上のとき。
		m_gaugeState = en10Then;						//状態を変更する。
	}
	if (m_scale.x < 0.1f) {								//１０％未満のとき。
		m_gaugeState = en10Less;						//状態を変更する。
	}

	ModelChange();										//モデルを変更する処理。

	m_oldGaugeState = m_gaugeState;						//状態のバックアップをとっておく。
}

//モデルを変更する処理。
void TimeLimitGauge::ModelChange()
{
	if (m_gaugeState != m_oldGaugeState)				//状態が変更されたとき。
	{
		switch (m_gaugeState)			//状態。
		{
		case en66Then:			//スケールが66％以上のとき。
			m_spriteRender->Init(L"Assets/sprite/gauge_1.dds", size_x, size_y);
			break;

		case en33Then:			//33％以上のとき。
			m_spriteRender->Init(L"Assets/sprite/gauge_2.dds", size_x, size_y);
			break;

		case en10Then:			//10％以上のとき。
			m_spriteRender->Init(L"Assets/sprite/gauge_3.dds", size_x, size_y);
			break;

		case en10Less:			//10％未満のとき。
			m_spriteRender->Init(L"Assets/sprite/gauge_4.dds", size_x, size_y);
			break;
		}
	}
}

//スケールの変更。
void TimeLimitGauge::ChangeScale()
{
	if (m_scale_x > 0.f)			//拡大率が０より大きいとき。
	{
		m_scale_x -= 1.f / 120.f / 60.f;		//todo 60.fは実際はGetFlameDeltaTime。
	}

	m_scale.x = m_scale_x;			//スケールを代入。
}

//縮小時間を指定する場合のスケールの変更。
void TimeLimitGauge::ChangeScale(float time)
{
	if (m_scale_x > 0.f)			//拡大率が０より大きいとき。
	{
		m_scale_x -= 1.f / time / 60.f;		//todo 60.fは実際はGetFlameDeltaTime。
	}

	m_scale.x = m_scale_x;			//スケールを代入。
}

//更新処理。
void TimeLimitGauge::Update()
{
	//状態を変更する。
	StateChange();

	m_scale.x = m_scale_x;			//スケールを代入。

	m_spriteRender->SetPosition(m_position);		//座標更新。
	m_spriteRender->SetScale(m_scale);				//拡大処理。


	if (m_scale.x > 0.f && m_timeLimitFlag == true) {		//拡大率が０より大きいとき。且つフラグがtrueのとき。
		m_timeLimitFlag = false;		//フラグを返す。
	}

	if (m_scale.x <= 0.f && m_timeLimitFlag == false) {		//拡大率が０のとき。且つフラグがfalseのとき。
		m_timeLimitFlag = true;			//フラグを返す。
	}


}
