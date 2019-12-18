#include "stdafx.h"
#include "Belongings.h"
#include "Pot.h" 
#include "Dish.h"

Belongings::Belongings()
{

}


Belongings::~Belongings()
{
}

bool Belongings::Start()
{

	return true;
}

void Belongings::SetSoupBase(Belongings* puttingBelongings)
{
	Pot* pot = (Pot*)puttingBelongings;		//�ǂ�Pot��������������B	
	pot->Soup();				//�X�[�v�̑f�𐶐�����B	
}

//�X�[�v�����������B
void Belongings::DeleteSoup(Belongings* belongings)
{
	Pot* pot = (Pot*)belongings;
	pot->DeleteLikeSoup();
}

int Belongings::GetPotFoosType(Belongings* powt)
{
	Pot* pot = (Pot*)powt;

	return	pot->GetPutSoupFoods();
}
void Belongings::SetPotFoodType(Belongings* powt, int fooType)
{
	Pot* pot = (Pot*)powt;
	pot->SetPutSoupFoods(fooType);
}

void Belongings::PotGaugeExpansion(Belongings* belongings)
{
	Pot* pot = (Pot*)belongings;
	pot->PotGaugeExpansion();
}

//���M�ɐH�ו���u�������B
void Belongings::PutDishs(Belongings* belongings ,int FoodType)
{
	Dish* dish = (Dish*)belongings;
	dish->PutDish(FoodType);
}

// ���M�􂢏�̏d�˂Ă��邨�M���炨�M����Ƃ鏈���B
void Belongings::PutDishFromKitchen(Belongings* belongings, Kitchen* kitchen)
{
	Dish* dish = (Dish*)belongings;
	dish->DeleteDishList(kitchen);
}

// �Q�[�W�����A�g��A�摜�����ւ���S���֐��B
void Belongings::GaugeGeneration(bool enlargedDivision, float time, float numberOfTimer, bool checkGeneration)
{
	if (m_GaugeGenerationFlag == false) {			//�Q�[�W����������Ă��Ȃ���΁B
		m_gauge = NewGO<Gauge>(0, "gauge");			//�Q�[�W�𐶐�����B
		m_gaugePos = m_position;					//�Q�[�W�̍��W�Ƀ��f���̍��W�����B
		m_gaugePos.x -= 50.f;						//���Ɋ񂹂�B
		m_gaugePos.y += 100.f;						//Y���������グ�Ă��B
		m_gaugePos.z -= 70.f;						//������O�Ɋ񂹂�B	
		m_gauge->SetPosition(m_gaugePos);			//�Q�[�W�̍��W���X�V�B
		m_GaugeGenerationFlag = true;				//�Q�[�W���������ꂽ�̂Ńt���O��Ԃ��B
	}

	if (m_gauge != nullptr) {						//�Q�[�W����������Ă����Ȃ�΁B
		if (enlargedDivision) {						//�g�啪��������ꍇ�B
			m_gauge->Magnification(time, numberOfTimer);			//�Q�[�W���g�傷��B
		}

		if (enlargedDivision == false) {			//�g�啪�������Ȃ��ꍇ�B
			m_gauge->Expansion(time);				//�Q�[�W���g�傷��B
		}
	}

	if (m_gauge != nullptr && m_gauge->GetGaugeMax())			//�Q�[�W���ő�ɂȂ�����B
	{
		if (m_identification == enFood) {			//�H�ו��̂Ƃ��B
			m_foodState = enCutting;				//�H�ו��̏�Ԃ�؂�ꂽ��ԂɁB
		}
		DeleteGO(m_gauge);							//�Q�[�W�������B
		m_gauge = nullptr;							//�Q�[�W�̃C���X�^���X�������B
		if (checkGeneration == false) {
			m_GaugeGenerationFlag = false;
		}
		if (checkGeneration) {						//���������܁[���𐶐����鏈���̂Ƃ��B
			m_check = NewGO<Check>(0, "check");		//�`�F�b�N�}�[�N�𐶐�����B
			m_gaugePos = m_position;
			m_gaugePos.y += 100.f;			//Y���������グ�Ă��B
			m_gaugePos.z -= 70.f;
			m_check->SetPosition(m_gaugePos);
		}
	}
}

//�Q�[�W�̍��W�X�V�B
void Belongings::GaugePosUpdate()
{
	if (m_gauge != nullptr)
	{
		m_gaugePos = m_position;
		m_gaugePos.x -= 50.f;			//���Ɋ񂹂�B
		m_gaugePos.y += 100.f;			//Y���������グ�Ă��B
		m_gaugePos.z -= 70.f;
		m_gauge->SetPosition(m_gaugePos);
	}

	if (m_check != nullptr) {
		m_gaugePos = m_position;
		m_gaugePos.y += 100.f;			//Y���������グ�Ă��B
		m_gaugePos.z -= 70.f;
		m_check->SetPosition(m_gaugePos);
		m_checkDeleteTimer += 1.f / 60.f;

		if (m_checkDeleteTimer >= 1.f) {
			DeleteGO(m_check);
			m_check = nullptr;
		}
	}
}

void Belongings::DeleteGauge()
{
	DeleteGO(m_gauge);
	DeleteGO(m_check);
}

void Belongings::Update()
{

}
