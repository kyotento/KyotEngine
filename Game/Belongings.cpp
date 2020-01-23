#include "stdafx.h"
#include "Belongings.h"
#include "Pot.h" 
#include "Dish.h"

namespace {
	float cleckDeleteTiming = 0.5f;			//�N���b�N�A�C�R������������Ă��������܂ł̎��ԁB
}

Belongings::Belongings()
{

}


Belongings::~Belongings()
{
	//���f�����q������Ă��Ȃ��Ƃ��������s��Ȃ��B
	if (m_skinModelRender == nullptr) {
		return;
	}

	DeleteGO(m_skinModelRender);			//�X�L�����f���������B
	m_skinModelRender = nullptr;

	DeleteGauge();
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

// ����ɓ����Ă���H�ו��̎�ނ���������B
int Belongings::GetPotFoosType(Belongings* powt)
{
	Pot* pot = (Pot*)powt;
	return	pot->GetPutSoupFoods();
}

// ����ɓ����Ă��鐷����闿���������B
int Belongings::GetGetPotDishCuisine(Belongings* powt)
{
	Pot* pot = (Pot*)powt;
	return pot->GetPotDishCuisine();
}

// ����ɓ����H�ו��̎�ނ�ݒ肷��B
void Belongings::SetPotFoodType(Belongings* powt, int foodType)
{
	Pot* pot = (Pot*)powt;
	pot->SetPutSoupFoods(foodType);
}

// ����̃Q�[�W�g�又���B
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
		m_gaugePos.x -= 50.f;						
		m_gaugePos.y += 100.f;						
		m_gaugePos.z -= 70.f;							
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
			m_gaugePos.y += 100.f;			
			m_gaugePos.z -= 70.f;
			m_check->SetPosition(m_gaugePos);		//���W�X�V�B
		}
	}
}

//�Q�[�W�̍��W�X�V�B
void Belongings::GaugePosUpdate()
{
	if (m_gauge != nullptr)
	{
		m_gaugePos = m_position;
		m_gaugePos.x -= 50.f;			
		m_gaugePos.y += 100.f;			
		m_gaugePos.z -= 70.f;
		m_gauge->SetPosition(m_gaugePos);			//���W�X�V�B
	}

	if (m_check != nullptr) {
		m_gaugePos = m_position;
		m_gaugePos.y += 100.f;			
		m_gaugePos.z -= 70.f;
		m_check->SetPosition(m_gaugePos);							//���W�X�V�B
		m_checkDeleteTimer += gametime().GetFrameDeltaTime();		//�^�C�}�[���X�V�B

		if (m_checkDeleteTimer >= cleckDeleteTiming) {				//��莞�Ԍo�߂������B
			DeleteGO(m_check);			//�A�C�R���������B
			m_check = nullptr;
		}
	}
}

//�Q�[�W�̂����������B
void Belongings::DeleteGauge()
{
	if (m_gauge != nullptr) {
		DeleteGO(m_gauge);
	}
	if (m_check != nullptr) {
		DeleteGO(m_check);
	}
}

//���M�ɍڂ��Ă��闿�����w�肷��B
void Belongings::SetDishCuisine(Belongings* belongings, int dishCuisine)
{
	Dish* dish = (Dish*)belongings;
	dish->SetDishCuisine(dishCuisine);			//���M�ɍڂ��Ă��闿�����w�肷��B
}

//���M�ɍڂ��Ă��闿�����擾����B
int Belongings::GetDishCuisine(Belongings* belongings)
{
	Dish* dish = (Dish*)belongings;
	return dish->GetDishCuisine();
}

void Belongings::Update()
{

}
