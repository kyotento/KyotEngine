#include "stdafx.h"
#include "GameOver.h"

namespace {
	float m_size_w = 900.f;
	float m_size_h = 180.f;
}

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
	DeleteGO(m_spriteRender);
}

bool GameOver::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");							//�摜�����N���X�𐶐��B
	m_spriteRender->Init(L"Assets/sprite/TimeUp.dds", m_size_w, m_size_h);		//�������B
	m_spriteRender->SetPosition(m_position);									//�摜�𐶐��B
	m_spriteRender->SetScale(m_scale);											//�X�P�[�����X�V�B

	return true;
}

//�X�P�[���̍X�V�����B
void GameOver::ScaleUpdate()
{
	if (m_scalefloat <= 1.f) {				//�X�P�[�����P�ȉ��̂Ƃ��B
		m_scalefloat += 0.02f;				//�X�P�[�����g��B

		m_scale = { m_scalefloat,m_scalefloat,m_scalefloat };		//�X�P�[�������B
	}
}

//�t�B�[���h�̂��̂����ׂď��������B
void GameOver::DeleteField()
{

}

void GameOver::Update()
{
	ScaleUpdate();			//�X�P�[�����X�V�B

	if (m_spriteRender != nullptr) {				//�摜����������Ă���Ƃ��B
		m_spriteRender->SetScale(m_scale);			//�X�P�[�����X�V�B
		m_timer += gametime().GetFrameDeltaTime();		//�^�C�}�[���X�V�B
	}

	if (m_timer >= 5.f) {			//�^�C�}�[���R�ȏ�̂Ƃ��B

		//todo������Fade������A
		DeleteField();				//�t�B�[���h�������B		

		m_result = NewGO<Result>(0, "result");			//���U���g��\���B

		DeleteGO(this);				//�N���X�������B
	}

}
