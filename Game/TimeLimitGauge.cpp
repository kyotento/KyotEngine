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

//��Ԃ�ύX���鏈���B
void TimeLimitGauge::StateChange()
{
	if (m_scale.x >= 0.66f) {							//�Q�[�W�̃X�P�[�����U�U���ȏ�̂Ƃ��B
		m_gaugeState = en66Then;						//��Ԃ�ύX����B
	}
	if (m_scale.x < 0.66f && m_scale.x >= 0.33f) {		//�R�R���ȏ�̂Ƃ��B
		m_gaugeState = en33Then;						//��Ԃ�ύX����B
	}
	if (m_scale.x < 0.33f&& m_scale.x >= 0.1f) {		//�P�O���ȏ�̂Ƃ��B
		m_gaugeState = en10Then;						//��Ԃ�ύX����B
	}
	if (m_scale.x < 0.1f) {								//�P�O�������̂Ƃ��B
		m_gaugeState = en10Less;						//��Ԃ�ύX����B
	}

	ModelChange();										//���f����ύX���鏈���B

	m_oldGaugeState = m_gaugeState;						//��Ԃ̃o�b�N�A�b�v���Ƃ��Ă����B
}

//���f����ύX���鏈���B
void TimeLimitGauge::ModelChange()
{
	if (m_gaugeState != m_oldGaugeState)				//��Ԃ��ύX���ꂽ�Ƃ��B
	{
		switch (m_gaugeState)			//��ԁB
		{
		case en66Then:			//�X�P�[����66���ȏ�̂Ƃ��B
			m_spriteRender->Init(L"Assets/sprite/gauge_1.dds", size_x, size_y);
			break;

		case en33Then:			//33���ȏ�̂Ƃ��B
			m_spriteRender->Init(L"Assets/sprite/gauge_2.dds", size_x, size_y);
			break;

		case en10Then:			//10���ȏ�̂Ƃ��B
			m_spriteRender->Init(L"Assets/sprite/gauge_3.dds", size_x, size_y);
			break;

		case en10Less:			//10�������̂Ƃ��B
			m_spriteRender->Init(L"Assets/sprite/gauge_4.dds", size_x, size_y);
			break;
		}
	}
}

//�X�V�����B
void TimeLimitGauge::Update()
{
	//��Ԃ�ύX����B
	StateChange();
}
