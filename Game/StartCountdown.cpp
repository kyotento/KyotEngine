#include "stdafx.h"
#include "StartCountdown.h"

namespace {
	float m_ready_w = 720.f;		//Ready�摜�̕��B
	float m_ready_h = 180.f;		//Ready�摜�̍����B
	float m_start_w = 360.f;		//Start�摜�̕��B
	float m_start_h = 180.f;		//Start�摜�̍����B
}

StartCountdown::StartCountdown()
{
}


StartCountdown::~StartCountdown()
{
	if (m_spriteRenderReady != nullptr) {		//��������Ă�����B
		DeleteGO(m_spriteRenderReady);			//�����B
	}
	if (m_spriteRenderStart != nullptr) {		//��������Ă�����B
		DeleteGO(m_spriteRenderStart);			//�����B
	}
}

bool StartCountdown::Start()
{

	return true;
}

//�X�P�[���̍X�V�����B
void StartCountdown::ScaleUpdate()
{
	if (m_scale < 1.f) {			//�X�P�[�����P�ȉ��̂Ƃ��B
		m_scale += 0.05f;			//�X�P�[�������Z�B
	}

	//todo �������Ӗ��Ȃ����B
	m_scaleReady = { m_scale,m_scale,m_scale };			//Ready�̃X�P�[����ύX�B
	m_scaleStart = { m_scale,m_scale,m_scale };			//Start�̃X�P�[����ύX�B

}

void StartCountdown::Update()
{
	if (m_newReady == false) {			//Renady����x����������Ă��Ȃ��Ƃ��B
		m_spriteRenderReady = NewGO<SpriteRender>(0, "sprite");								//�X�v���C�g�N���X�𐶐��B
		m_spriteRenderReady->Init(L"Assets/sprite/ready.dds", m_ready_w, m_ready_h);		//�������B
		m_spriteRenderReady->SetPosition(m_position);										//���W�X�V�B
		m_spriteRenderReady->SetScale(m_scaleReady);										//�X�P�[�����X�V�B
		m_newReady = true;				//�������ꂽ�̃t�O��Ԃ��B
	}

	//�X�P�[���̍X�V�����B
	ScaleUpdate();

	if (m_spriteRenderReady != nullptr) {							//Ready�̉摜����������Ă�����B
		m_spriteRenderReady->SetScale(m_scaleReady);				//�X�P�[�����X�V�B

		if (m_scale >= 1.f) {										//�X�P�[�����P�ȏ�̂Ƃ��B
			m_deleteTimer += gametime().GetFrameDeltaTime();		//�^�C�}�[���X�V�B
			if (m_deleteTimer >= 1.f) {								//1�b�ȏ�o�߂������B
				DeleteGO(m_spriteRenderReady);						//Ready�̉摜�������B
				m_spriteRenderReady = nullptr;						//�C���X�^���X��j���B
				m_scale = 0.f;										//�X�P�[��������������B
				m_deleteTimer = 0.f;								//�^�C�}�[���������B
			}
		}
	}

	if (m_spriteRenderReady == nullptr && m_newReady) {				//Ready�̉摜�̃C���X�^���X��null���A��x��������Ă������B
		if (m_newStart == false) {			//Start����x����������Ă��Ȃ��Ƃ��B
			m_spriteRenderStart = NewGO<SpriteRender>(0, "sprite");								//�X�v���C�g�N���X�𐶐��B
			m_spriteRenderStart->Init(L"Assets/sprite/start.dds", m_start_w, m_start_h);		//�������B
			m_spriteRenderStart->SetPosition(m_position);										//���W���w��B
			m_spriteRenderStart->SetScale(m_scaleStart);										//�X�P�[�����X�V�B
			m_newStart = true;																	//��x�������ꂽ�̂Ńt���O��Ԃ��B
		}	

		if (m_newStart) {			//��x��������Ă���B
			if (m_spriteRenderStart != nullptr) {							//Start�̉摜�𐶐����Ă�����B
				m_spriteRenderStart->SetScale(m_scaleStart);				//�X�P�[�����X�V�B
				if (m_scale >= 1.f) {			//�X�P�[�����P�ȏ�̂Ƃ��B
					m_deleteTimer += gametime().GetFrameDeltaTime();		//�^�C�}�[���X�V�B
					if (m_deleteTimer >= 1.f) {								//�^�C�}�[��1�ȏ�̂Ƃ��B
						DeleteGO(m_spriteRenderStart);						//Start�̉摜�������B
						m_spriteRenderStart = nullptr;						//�C���X�^���X��j���B
						m_gameStartFlag = true;								//�Q�[�ނ̍X�V�������J�n�B
					}
				}
			}
		}
	}
}