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
	m_skinModelRender = nullptr;
}

bool Gauge::Start()
{
#ifdef GAUGE_TEST

	////�Q�[�W�̊�ՁB
	m_skinModelRender = NewGO<SkinModelRender>(1, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/2D/Gauge/GaugeSheet.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale({ 1.f,1.f,1.f });

#endif

	//�Q�[�W�B
	m_skinModelRenderGauge = NewGO<SkinModelRender>(2, "skinModel");
	m_skinModelRenderGauge->Init(L"Assets/modelData/2D/Gauge/Gauge.cmo", nullptr, 0, "PSMain", "VSMain", true, false);
	m_skinModelRenderGauge->SetPosition(m_position);
	m_skinModelRenderGauge->SetScale({ m_x, 1.f, 1.f });

	return true;
}

//�Q�[�W���g�傷�鏈���B
void Gauge::Expansion(float time)
{
	float ExpensionSpeed;
	ExpensionSpeed = 1 / (time * 60.f);		//�����b�Ŋg�嗦���P�ɂ��邽�߂̌v�Z�B

	if (m_skinModelRenderGauge != nullptr) {
		if (m_x <= 1.f)		//�g�嗦���P�ȉ��̂Ƃ��B
		{
			m_x += ExpensionSpeed;	//�g�傷��B
			m_skinModelRenderGauge->SetScale({ m_x,1.f,1.f });		//�g����X�V�B
		}
	}
}

//�Q�[�W���g�傷�鏈���B
void Gauge::Magnification(float time, float numberOfTimes)
{
	if (m_x < 1.f) {								//�g�嗦���P�ȉ��̂Ƃ��B
		float x = 1 / numberOfTimes;				//�g�嗦���v�Z�B
		m_expansionTimer += 1.f / 60.f;				//�^�C�}�[���v�Z����B
		float TimeInterval = time / numberOfTimes;	//�g�厞�ԊԊu���v�Z�B

		if (m_expansionTimer >= TimeInterval) {		//�^�C�}�[���g�厞�ԊԊu�ȏ�̂Ƃ��B
			m_x += x;								//�g�嗦�����Z�B
			m_expansionTimer = 0.f;					//�^�C�}�[�����Z�b�g�B
			m_skinModelRenderGauge->SetScale({ m_x,1.f,1.f });		//�X�P�[�����X�V�B
		}
	}
	else
	{			//�g�嗦���P�𒴂������B
		m_gaugeMax = true;		//�Q�[�W���ő�ɂȂ����̂Ńt���O��Ԃ��B
	}
}

// �Q�[�W�̊g�嗦�ɉ����ăt���O��Ԃ��B
void Gauge::ChangeGaugeMax()
{
	if (m_gaugeMax == false && m_x >= 1.f)
	{
		m_gaugeMax = true;
	}

	if (m_gaugeMax == true && m_x < 1.f)
	{
		m_gaugeMax = false;
	}
}

void Gauge::Update()
{
	CVector3 oldPosition = m_position;
	m_skinModelRenderGauge->SetPosition(m_position);	//�Q�[�W�̍��W���X�V�B

	ChangeGaugeMax();				// �Q�[�W�̊g�嗦�ɉ����ăt���O��Ԃ��B

#ifdef GAUGE_TEST

	m_skinModelRender->SetPosition(m_position);			//���W���X�V�B

#endif
}