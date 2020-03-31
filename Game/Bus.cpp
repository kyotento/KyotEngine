#include "stdafx.h"
#include "Bus.h"

//#define DEBUG			//�f�o�b�O����`����B
namespace {
	float a = 0;
	const float fallSpeed = 9.8f;				//�������x�B 
	const float moveSpeed = 10.f;				//�ړ����x�B
	const float judgmentDistance = 100.f;		//���Ƃ̔��苗���B

	const float playerCollidedRadius = 45.f;			//�J�v�Z���R���C�_�[�̔��a�B
	const float playerCollidedHeight = 50.f;			//�J�v�Z���R���C�_�[�̍����B

	CVector3 camerapos = { 0,900.f,-600.f };			//�����_����J�����̍��W���w�肷�邽�߂̒l�B
}

Bus::Bus()
{
}


Bus::~Bus()
{
	DeleteGO(m_skinModelRender);
}


bool Bus::Start()
{

	m_gameCamera = FindGO<GameCamera>("gamecamera");

	//�o�X�̃��f���������X�B
	m_skinModelRender = NewGO<SkinModelRender>(0, "skinmodel");
	m_skinModelRender->Init(L"Assets/modelData/bus/bus.cmo");
	m_skinModelRender->InitNormalMap(L"Assets/sprite/bus_Normal.dds");
	m_skinModelRender->InitSpecMap(L"Assets/sprite/bus_spec.dds");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	m_resetPosition = m_position;			//�������W���o�b�N�A�b�v�B

	m_characon.Init(playerCollidedRadius, playerCollidedHeight, m_position);

	return true;
}

//�ړ������B
void Bus::Move()
{
	m_stickPower.x = g_pad[0].GetLStickXF();		//���X�e�B�b�N��X���̌X���B
	m_stickPower.y = 0.f;							//���X�e�B�b�N��Y���B
	m_stickPower.z = g_pad[0].GetLStickYF();		//���X�e�B�b�N��Z���̌X���B

	m_move = m_stickPower * moveSpeed;				//�ړ����x�̌v�Z�B
	m_move.y -= fallSpeed;							//�������x�̌v�Z�B
	m_position = m_characon.Execute(1.0, m_move);	//�L�����R���Ɉړ����x�����B

	m_skinModelRender->SetPosition(m_position);
}

//��]�����B
void Bus::Rotation()
{
	CVector3 m_YisDie;
	m_YisDie = m_move;					//�ړ����x(��������)�����B
	m_YisDie.y = 0.0f;					//Y���͕K�v�Ȃ��̂�0�����B
	m_YisDie.Normalize();				//���K�����Č��������߂�B
	m_rotation.SetRotation({ 0.0f,  1.0f,  0.0f }, atan2f(m_YisDie.x, m_YisDie.z));			//��]���v�Z�B

	//�ړ����Ă����ꍇ�̂݉�]���X�V����B
	if (m_YisDie.Length() > 0.01f) {							
		m_skinModelRender->SetRotation(m_rotation);			
	}
}

//�J������Ǐ]�����鏈���B
void Bus::FollowCamera()
{
	m_gameCamera->SetTarget(m_position);
	CVector3 cameraPos = m_position + camerapos;
	m_gameCamera->SetPosition(cameraPos);
}

//���Ɍ����������鏈�����X�B
void Bus::FlagSearch()
{
	//���̃C���X�^���X���擾�B
	m_flag[0] = FindGO<Flag>("flag1");
	m_flag[1] = FindGO<Flag>("flag2");
	m_flag[2] = FindGO<Flag>("flag3");

	//�ڍ׉摜�����p�N���X�̃C���X�^���X���擾����B
	m_stageSelectDetailed = FindGO<StageSelectDetailed>("stageselectdetailed");
 
	//���Ƃ̋���������Ƃ�B
	for (int i = 0; i < FLAG_NUM; i++) {
		CVector3 vectorLength;			//���ƃo�X�̋����i�[�p�B
		vectorLength = m_position - m_flag[i]->GetPosition();		

		//��苗���ȓ��������ꍇ�B
		if (vectorLength.Length() < judgmentDistance) {
			m_flag[i]->NewButton();
			m_stageSelectDetailed->NewDetailedImage(i);		//�C���[�W�摜�𐶐��B
		}
		//�͈͊O���������B
		else{
			m_flag[i]->DeleteButton();
		}

	}
	//���ׂĂ̊����͈͊O�̂Ƃ��B
	if ((m_position - m_flag[0]->GetPosition()).Length() > judgmentDistance
		&& (m_position - m_flag[1]->GetPosition()).Length() > judgmentDistance
		&& (m_position - m_flag[2]->GetPosition()).Length() > judgmentDistance) {
		m_stageSelectDetailed->DeleteDetailedImage();
	}
}

void Bus::Update()
{
	//�f�o�b�O�B
#ifdef DEBUG
	a += gametime().GetFrameDeltaTime();
	m_rotation.SetRotation(CVector3::AxisY(), 1);			//��]���v�Z�B
	m_skinModelRender->SetRotation(m_rotation);

#endif

	FollowCamera();		//�J������Ǐ]�����鏈���B
	Move();				//�ړ������B
	Rotation();			//��]�����B
	FlagSearch();		//���Ɍ����������鏈�����X�B
}