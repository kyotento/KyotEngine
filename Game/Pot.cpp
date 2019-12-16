#include "stdafx.h"
#include "Pot.h"

namespace {
	CVector3 checkPos;		//�`�F�b�N�}�[�N�̍��W�B
}

Pot::Pot()
{
	//�������Ǝ��ʁB
	m_identification = enKitchenWare;
}

Pot::~Pot()
{
}

bool Pot::Start()
{
	m_skinModelRender->Init(L"Assets/modelData/Pot/Pot.cmo");		//�������A
	m_skinModelRender->SetPosition(m_position);						//���W�w��B
	m_skinModelRender->SetRotation(m_rotation);

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
		m_soupPos.x = m_position.x;		//���X���W���X�[�v��X���W�ɑ���B
		m_soupPos.z = m_position.z;		//���Z���W���X�[�v��Z���W�ɑ���B
		m_soupBase->SetPosition(m_soupPos);				//�X�[�v�̍��W��ݒ肷��B
		m_soupBase->DecideTheSoupType(m_putSoupFoods);	//��������X�[�v�����߂�B
		m_potState = enOne;								//�|�b�g�ɐH�ו���������Ă����ԂɁB
		m_gauge = NewGO<Gauge>(0, "gauge");				//�Q�[�W�𐶐�����B
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
	if (m_gauge != nullptr) {							//�Q�[�W����������Ă�����B
		m_gauge->Expansion(10.f);						//�Q�[�W�̊g�又���B
	}
	if (m_check != nullptr || m_danger != nullptr) {
		m_dangerStartTimer += 1.f / 60.f;		//todo�@���ۂ�getFrameDeltaTime�B
	}
}

//2D�̍��W�X�V�֐��B
void Pot::Vector2DUpdate()
{
	//�Q�[�W�̍��W�X�V�B
	m_gaugePos = m_position;		//�Q�[�W�̍��W�ɂ���̍��W�ɑ���B
	m_gaugePos.x -= 50.f;			//���Ɋ񂹂�B
	m_gaugePos.y += 100.f;			//Y���������グ�Ă��B
	m_gaugePos.z -= 70.f;			//������O�ɁB

}

//�댯�}�[�N�`�揈���B
void Pot::Danger2D()
{
	if (m_dangerFlag == false && m_dangerStartTimer >= 5.f && m_dangerStartTimer <= 15.f) {		//�댯�}�[�N����������Ă��Ȃ��A���^�C�}�[���o�߂��Ă������B
		m_danger = NewGO<Danger>(0, "danger");			//�摜�𐶐��B
		DeleteGO(m_check);								//�`�F�b�N�}�[�N�������B
		m_check = nullptr;								//�`�F�b�N�}�[�N�̃C���X�^���X�������B
		m_dangerFlag = true;							//�����t���O��Ԃ��B
	}
	if (m_danger != nullptr) {							//�댯�}�[�N����������Ă���Ƃ��B
		m_danger->SetPosition(checkPos);				//���W�X�V�B
	}
}

//�Ύ��}�[�N�`�揈���B
void Pot::Fire2D()
{
	if (m_fireFlag == false && m_dangerStartTimer > 15.f) {		//�Ύ��}�[�N����������Ă��Ȃ��A���^�C�}�[���o�߂��Ă������B	
		m_fire = NewGO<Fire>(0, "fire");				//�摜�𐶐��B
		DeleteGO(m_danger);								//�댯�}�[�N�������B
		m_danger = nullptr;								//�댯�}�[�N�̃C���X�^���X�������B
		m_dangerFlag = false;							//��������ĂȂ��̂Ńt���O��Ԃ��B
		m_fireFlag = true;								//�����t���O��Ԃ��B
	}
	if (m_fire != nullptr) {							//�Ύ��}�[�N����������Ă���Ƃ��B
		m_fire->SetPosition(checkPos);				//���W���X�V�B
	}
}

void Pot::Update()
{
	m_skinModelRender->SetPosition(m_position);		//���W���X�V�B
	m_skinModelRender->SetRotation(m_rotation);		//��]���X�V�B
	m_soupPos.x = m_position.x;		//���X���W���X�[�v��X���W�ɑ���B
	m_soupPos.z = m_position.z;		//���Z���W���X�[�v��Z���W�ɑ���B

	if (m_soupBase != nullptr) {						//�X�[�v����������Ă�����B
		m_soupBase->SetPosition(m_soupPos);				//�X�[�v�̍��W���w��B
	}
	if (m_gauge != nullptr) {							//�Q�[�W����������Ă�����B
		m_gauge->SetPosition(m_gaugePos);				//�Q�[�W�̍��W���w��B
	}

	StateChange();										//��ԕω��B
	Vector2DUpdate();									//2D�̍��W�X�V�B
	Danger2D();											//�댯�}�[�N�`�揈���B
	Fire2D();											//�Ύ��}�[�N�`�揈���B
}