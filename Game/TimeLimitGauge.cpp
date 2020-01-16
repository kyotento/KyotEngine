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

//�X�P�[���̕ύX�B
void TimeLimitGauge::ChangeScale()
{
	if (m_scale_x > 0.f)			//�g�嗦���O���傫���Ƃ��B
	{
		m_scale_x -= 1.f / 120.f / 60.f;		//todo 60.f�͎��ۂ�GetFlameDeltaTime�B
	}

	m_scale.x = m_scale_x;			//�X�P�[�������B
}

//�k�����Ԃ��w�肷��ꍇ�̃X�P�[���̕ύX�B
void TimeLimitGauge::ChangeScale(float time)
{
	if (m_scale_x > 0.f)			//�g�嗦���O���傫���Ƃ��B
	{
		m_scale_x -= 1.f / time / 60.f;		//todo 60.f�͎��ۂ�GetFlameDeltaTime�B
	}

	m_scale.x = m_scale_x;			//�X�P�[�������B
}

//�X�V�����B
void TimeLimitGauge::Update()
{
	//��Ԃ�ύX����B
	StateChange();

	m_scale.x = m_scale_x;			//�X�P�[�������B

	m_spriteRender->SetPosition(m_position);		//���W�X�V�B
	m_spriteRender->SetScale(m_scale);				//�g�又���B


	if (m_scale.x > 0.f && m_timeLimitFlag == true) {		//�g�嗦���O���傫���Ƃ��B���t���O��true�̂Ƃ��B
		m_timeLimitFlag = false;		//�t���O��Ԃ��B
	}

	if (m_scale.x <= 0.f && m_timeLimitFlag == false) {		//�g�嗦���O�̂Ƃ��B���t���O��false�̂Ƃ��B
		m_timeLimitFlag = true;			//�t���O��Ԃ��B
	}


}
