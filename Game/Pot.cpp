#include "stdafx.h"
#include "Pot.h"


Pot::Pot()
{
	//�������Ǝ��ʁB
	m_identification = enKitchenWare;
}


Pot::~Pot()
{
//	DeleteGO(m_skinModelRender);
}


bool Pot::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Pot/Pot.cmo");		//�������A
	m_skinModelRender->SetPosition(m_position);						//���W�w��B

	m_soupPos = m_position;			//�X�[�v�̍��W������̍��W�ɑ���B

	return true;
}

//�X�[�v���������ꂽ�Ƃ��̏����B
void Pot::Soup()
{
	if (m_potState == enTwo) {						//�H�ו���������Ă����ԁB
		m_soupPos.y += 25.f;						//�H�ו����������悤�Ɍ����邽�߂�Y���W���グ��B
		m_gauge->GaugeHalf();						//�Q�[�W�̃X�P�[���𔼕��ɂ���B
		m_potState = enThree;						//�H�ו����O��������Ԃɂ���B
	}

	if (m_potState == enOne) {							//�H�ו���������Ă����Ԃ̂Ƃ��B
		m_soupPos.y += 25.f;							//�H�ו����������悤�Ɍ����邽�߂�Y���W���グ��B
		m_potState = enTwo;								//�|�b�g�ɐH�ו���������Ă����ԁB
		m_gauge->GaugeHalf();							//�Q�[�W�̃X�P�[���𔼕��ɂ���B
	}

	if (m_potState == enZero) {							//�|�b�g�ɉ��������Ă��Ȃ��Ƃ��B
		m_soupBase = NewGO<SoupBase>(0, "soup");		//�X�[�v�̕����𐶐�����B
		m_soupBase->DecideTheSoupType(m_putSoupFoods);	//��������X�[�v�����߂�B
		m_potState = enOne;								//�|�b�g�ɐH�ו���������Ă����ԂɁB
		m_gauge = NewGO<Gauge>(0, "gauge");				//�Q�[�W�𐶐�����B
		m_gauge->SetPosition(m_gaugePos);				//�Q�[�W�̍��W���w��B
	}
}

void Pot::DeleteLikeSoup()
{
	m_potState = enZero;			//��Ԃ����������Ă��Ȃ���ԂɁB
	m_soupPos = m_position;			//���W�����ɖ߂��B
	DeleteGO(m_soupBase);			//�X�[�v�̃��f���������B
	DeleteGO(m_check);				//�`�F�b�N�}�[�N�������B
	m_check = nullptr;		
	m_checkFlag = false;			//�`�F�b�N�}�[�N�t���O��false�ɁB
}

//��ԕω��B
void Pot::StateChange()
{
	if (m_potState == enComplete)					//��̒��g���������Ă���Ƃ��B
	{
		DeleteGO(m_gauge);							//�Q�[�W�������B
		m_gauge = nullptr;							//�Q�[�W�̃C���X�^���X��null�ɁB
		if (m_checkFlag == false) {
			m_check = NewGO<Check>(0, "check");		//�`�F�b�N�}�[�N�𐶐��B
			m_check->SetPosition(m_position);		//���W���X�V�B
			m_checkFlag = true;						//�`�F�b�N�����t���O��true�ɁB
		}
	}

	if (m_potState == enThree)						//�H�ו����R�����Ă���Ƃ��B
	{
		if (m_gauge->GetGaugeMax()) {				//�Q�[�W���ő�l�̂Ƃ��B
			m_potState = enComplete;				//�H�ו��̏�Ԃ�������ԂɁB
		}
	}
}

void Pot::PotGaugeExpansion()
{
	if (m_gauge != nullptr) {							//�Q�[�W����������Ă�����B
		m_gauge->SetPosition(m_gaugePos);				//�Q�[�W�̍��W���w��B	
		//todo �� �R�����ɍڂ��Ă���Ƃ��B
		m_gauge->Expansion(10.f);						//�Q�[�W�̊g�又���B
	}
}

void Pot::Update()
{
	m_skinModelRender->SetPosition(m_position);		//���W���X�V�B
	m_soupPos.x = m_position.x;		//���X���W���X�[�v��X���W�ɑ���B
	m_soupPos.z = m_position.z;		//���Z���W���X�[�v��Z���W�ɑ���B
	m_gaugePos = m_position;		//�Q�[�W�̍��W�ɂ���̍��W�ɑ���B
	m_gaugePos.x -= 50.f;
	m_gaugePos.y += 100.f;			//Y���������グ�Ă��B
	m_gaugePos.z -= 70.f;

	if (m_soupBase != nullptr) {						//�X�[�v����������Ă�����B
		m_soupBase->SetPosition(m_soupPos);				//�X�[�v�̍��W���w��B
	}

	StateChange();										//��ԕω��B
}