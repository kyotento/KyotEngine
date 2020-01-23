#include "stdafx.h"
#include "Pot.h"
#include "StartCountdown.h"

namespace {
	float gaugeExpantionTime = 10.f;

	CVector3 checkPos;		//�`�F�b�N�}�[�N�̍��W�B
}

Pot::Pot()
{
	//�������Ǝ��ʁB
	m_identification = enKitchenWare;
}

Pot::~Pot()
{
	if (m_skinModelRender != nullptr) {
		DeleteGO(m_skinModelRender);		//�X�L�����f���������B
		m_skinModelRender = nullptr;
	}

	if (m_gauge != nullptr) {
		DeleteGO(m_gauge);					//�Q�[�W�������B
		m_gauge = nullptr;
	}

	DeleteLikeSoup();						//�X�[�v�����������B
}

bool Pot::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Pot/Pot.cmo");		//�������A
	m_skinModelRender->SetPosition(m_position);						//���W�w��B
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetSpecPower(2.f);							//�X�y�L�����̒l��ݒ�B

	m_soupPos = m_position;			//�X�[�v�̍��W������̍��W�ɑ���B

	return true;
}

//�X�[�v���������ꂽ�Ƃ��̏����B
void Pot::Soup()
{
	//�H�ו���������Ă����ԁB
	if (m_potState == enTwo) {							
		m_soupPos.y += 25.f;							//�H�ו����������悤�Ɍ����邽�߂�Y���W���グ��B
		m_gauge->GaugeHalf();							//�Q�[�W�̃X�P�[���𔼕��ɂ���B
		m_gauge->SetGaugeMax(false);				
		m_potState = enThree;							//�H�ו����O��������Ԃɂ���B
	}

	//�H�ו���������Ă����Ԃ̂Ƃ��B
	if (m_potState == enOne) {							
		m_soupPos.y += 25.f;							//�H�ו����������悤�Ɍ����邽�߂�Y���W���グ��B
		m_potState = enTwo;								//�|�b�g�ɐH�ו���������Ă����ԁB
		m_gauge->GaugeHalf();							//�Q�[�W�̃X�P�[���𔼕��ɂ���B
	}

	//�|�b�g�ɉ��������Ă��Ȃ��Ƃ��B
	if (m_potState == enZero) {							
		m_soupBase = NewGO<SoupBase>(0, "soup");		//�X�[�v�̕����𐶐�����B	
		m_soupPos.x = m_position.x;						//���X���W���X�[�v��X���W�ɑ���B
		m_soupPos.z = m_position.z;						//���Z���W���X�[�v��Z���W�ɑ���B
		m_soupBase->SetPosition(m_soupPos);				//�X�[�v�̍��W��ݒ肷��B
		m_soupBase->DecideTheSoupType(m_putSoupFoods);	//��������X�[�v�����߂�B
		m_potState = enOne;								//�|�b�g�ɐH�ו���������Ă����ԂɁB

		m_gauge = NewGO<Gauge>(0, "gauge");				//�Q�[�W�𐶐�����B
		m_gaugePos = m_position;						//�Q�[�W�̍��W�ɂ���̍��W�ɑ���B
		m_gaugePos.x -= 50.f;							//���Ɋ񂹂�B
		m_gaugePos.y += 100.f;							//Y���������グ�Ă��B
		m_gaugePos.z -= 70.f;							//������O�ɁB
		m_gauge->SetPosition(m_gaugePos);				//�Q�[�W�̍��W���w��B
	}
}

//todo �摜�̐؂�ւ���pot�ł��̂ł͂Ȃ��A�N���X������Ă�����ق������������B

//�X�[�v�����������B
void Pot::DeleteLikeSoup()
{
	m_potState = enZero;			//��Ԃ����������Ă��Ȃ���ԂɁB
	m_soupPos = m_position;			//���W�����ɖ߂��B
	DeleteGO(m_soupBase);			//�X�[�v�̃��f���������B

	if (m_check != nullptr) {		//��������Ă�����B
		DeleteGO(m_check);			//�`�F�b�N�}�[�N�������B
		m_check = nullptr;			//null�ɁB
	}
	if (m_danger != nullptr) {		//��������Ă�����B
		DeleteGO(m_danger);			//�댯�}�[�N�������B
		m_sound->Stop();			//�����~�߂�B
		m_danger = nullptr;			//null�ɁB
		m_dangerFlag = false;		//��������Ă��Ȃ��̂�false�ɕύX����B
	}
	if (m_fire != nullptr) {		//��������Ă�����B
		DeleteGO(m_fire);			//�Ύ��}�[�N�������B
		m_fire = nullptr;			//null�ɁB
		m_fireFlag = false;			//��������Ă��Ȃ��̂�false�ɕύX����B
	}

	m_checkFlag = false;			//�`�F�b�N�}�[�N�t���O��false�ɁB
	m_dangerStartTimer = 0.f;		//�^�C�}�[�����Z�b�g�B
}

//��ԕω��B
void Pot::StateChange()
{
	//�`�F�b�N�}�[�N�̍��W�X�V�B
	checkPos = m_position;			//�`�F�b�N�}�[�N�̍��W�ɂ���̍��W�����B
	checkPos.y += 100.f;			//Y���������グ�Ă��B
	checkPos.z -= 70.f;				//������O�ɁB

	if (m_potState == enComplete)					//��̒��g���������Ă���Ƃ��B
	{
		DeleteGO(m_gauge);							//�Q�[�W�������B
		m_gauge = nullptr;							//�Q�[�W�̃C���X�^���X��null�ɁB
		if (m_checkFlag == false) {					//�`�F�b�N�}�[�N����������Ă��Ȃ��Ȃ�B
			m_check = NewGO<Check>(0, "check");		//�`�F�b�N�}�[�N�𐶐��B		
			m_check->SetPosition(checkPos);			//���W�X�V�B
			m_checkFlag = true;						//�`�F�b�N�����t���O��true�ɁB
		}
		if (m_check != nullptr) {					//�`�F�b�N�}�[�N�̃C���X�^���X����������Ă����r�B
			m_check->SetPosition(checkPos);			//���W���X�V�B
		}
	}

	if (m_potState == enThree)						//�H�ו����R�����Ă���Ƃ��B
	{
		if (m_gauge->GetGaugeMax()) {				//�Q�[�W���ő�l�̂Ƃ��B
			m_potState = enComplete;				//�H�ו��̏�Ԃ�������ԂɁB
		}
	}
}

//�Q�[�W�̊g�又���B(���炪�R�����̏�ɂ��鎞�̂݌Ă΂��)�B
void Pot::PotGaugeExpansion()
{
	StartCountdown* startCountDown = FindGO<StartCountdown>("startcountdown");
	if (startCountDown->GetGameStartFlag()) {				//�Q�[���X�V�������J�n���Ă�����B
		if (m_gauge != nullptr) {							//�Q�[�W����������Ă�����B
			m_gauge->Expansion(gaugeExpantionTime);			//�Q�[�W�̊g�又���B
		}
		if (m_check != nullptr || m_danger != nullptr) {
			m_dangerStartTimer += gametime().GetFrameDeltaTime();		//�^�C�}�[���X�V�B
		}
	}
}

//�댯�}�[�N�`�揈���B
void Pot::Danger2D()
{
	if (m_dangerFlag == false && m_dangerStartTimer >= 3.f && m_dangerStartTimer <= 10.f) {		//�댯�}�[�N����������Ă��Ȃ��A���^�C�}�[���o�߂��Ă������B
		m_danger = NewGO<Danger>(0, "danger");			//�摜�𐶐��B
		checkPos = m_position;		//�Q�[�W�̍��W�ɂ���̍��W�ɑ���B
		checkPos.y += 100.f;		//Y���������グ�Ă��B
		checkPos.z -= 70.f;			//������O�ɁB
		m_danger->SetPosition(checkPos);				//���W�X�V�B
		DeleteGO(m_check);								//�`�F�b�N�}�[�N�������B
		m_check = nullptr;								//�`�F�b�N�}�[�N�̃C���X�^���X�������B
		m_dangerFlag = true;							//�����t���O��Ԃ��B

		//�댯���B
		m_sound = NewGO<Sound>(0, "sound");								//�T�E���h�N���X�𐶐��B
		m_sound->Init(L"Assets/sound/soundEffect/danger.wav", true);	//�������B
		m_sound->SetVolume(0.5f);										//�f�ނ̉����傫�������̂ŉ��ʂ�ύX�B
		m_sound->Play();												//�Đ��B
	}
	if (m_danger != nullptr) {							//�댯�}�[�N����������Ă���Ƃ��B
		checkPos = m_position;							//�Q�[�W�̍��W�ɂ���̍��W�ɑ���B
		checkPos.y += 100.f;							//Y���������グ�Ă��B
		checkPos.z -= 70.f;								//������O�ɁB
		m_danger->SetPosition(checkPos);				//���W�X�V�B
	}
}

//�Ύ��}�[�N�`�揈���B
void Pot::Fire2D()
{
	if (m_fireFlag == false && m_dangerStartTimer > 10.f) {		//�Ύ��}�[�N����������Ă��Ȃ��A���^�C�}�[���o�߂��Ă������B	
		m_fire = NewGO<Fire>(0, "fire");			//�摜�𐶐��B
		DeleteGO(m_danger);							//�댯�}�[�N�������B
		m_danger = nullptr;							//�댯�}�[�N�̃C���X�^���X�������B
		m_dangerFlag = false;						//��������ĂȂ��̂Ńt���O��Ԃ��B
		m_fireFlag = true;							//�����t���O��Ԃ��B
		m_sound->Stop();							//�댯�����~�߂�B
	}
	if (m_fire != nullptr) {						//�Ύ��}�[�N����������Ă���Ƃ��B
		checkPos = m_position;						//�Q�[�W�̍��W�ɂ���̍��W�ɑ���B
		checkPos.y += 100.f;						//Y���������グ�Ă��B
		checkPos.z -= 70.f;							//������O�ɁB
		m_fire->SetPosition(checkPos);				//���W���X�V�B
	}
}

//�Q�[�W�̍��W�X�V�����B
void Pot::GeugePosUpdate()
{
	//�Q�[�W�̍��W�X�V�B
	m_gaugePos = m_position;		//�Q�[�W�̍��W�ɂ���̍��W�ɑ���B
	m_gaugePos.x -= 50.f;			//���Ɋ񂹂�B
	m_gaugePos.y += 100.f;			//Y���������グ�Ă��B
	m_gaugePos.z -= 70.f;			//������O�ɁB

	m_skinModelRender->SetPosition(m_position);		//���W���X�V�B
	m_skinModelRender->SetRotation(m_rotation);		//��]���X�V�B
	m_soupPos.x = m_position.x;						//���X���W���X�[�v��X���W�ɑ���B
	m_soupPos.z = m_position.z;						//���Z���W���X�[�v��Z���W�ɑ���B

	if (m_soupBase != nullptr) {						//�X�[�v����������Ă�����B
		m_soupBase->SetPosition(m_soupPos);				//�X�[�v�̍��W���w��B
	}
	if (m_gauge != nullptr) {							//�Q�[�W����������Ă�����B
		m_gauge->SetPosition(m_gaugePos);				//�Q�[�W�̍��W���w��B
	}
}

// ����ɓ����Ă��邨�M�ɍڂ�\��̗����ύX����B
void Pot::ChangeCuisine()
{
	if (m_putSoupFoods == Belongings::enTomato) {			//�X�[�v���g�}�g�̂Ƃ��B
		m_potDishCuisine = CookingList::enTomatoSoup;		//��Ԃ�ύX�B
	}
	if (m_putSoupFoods == Belongings::enOnion) {			//�X�[�v���ʂ˂��̂Ƃ��B
		m_potDishCuisine = CookingList::enOnionSoup;		//��Ԃ�ύX�B
	}
}

void Pot::Update()
{
	GeugePosUpdate();			//�Q�[�W�̍��W�X�V�����B
	ChangeCuisine();			//����ɓ����Ă��邨�M�ɍڂ�\��̗����ύX����B		
	StateChange();				//��ԕω��B
	Danger2D();					//�댯�}�[�N�`�揈���B
	Fire2D();					//�Ύ��}�[�N�`�揈���B
}