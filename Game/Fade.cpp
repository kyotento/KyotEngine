#include "stdafx.h"
#include "Fade.h"

//todo �J�o�[�摜�Ȃ���Fade��\���ł���悤�ɂ���B(�����_�ł͉�)�B

namespace {
	float w = 1280.f;					//�摜�̕��B
	float h = 720.f;					//�摜�̍����B
	float scalePunching = 10.f;			//�g��k������������摜�̃X�P�[���B
	float interval = 0.f;				//�t�F�[�h�A�E�g���������Ă�����t�F�[�h�C���J�n�܂ł̃��O�B
	float fadeOutSizeLimit = 0.3f;		//�t�F�[�h�A�E�g���̍ŏ��X�P�[���B
}	

Fade::Fade()
{
}


Fade::~Fade()
{
	if (m_spriteRenderPunching != nullptr) {
		DeleteGO(m_spriteRenderPunching);
	}

	if (m_spriteRenderCover != nullptr) {
		DeleteGO(m_spriteRenderCover);
	}
}

bool Fade::Start()
{

	return true;
}

//�摜�𐶐�����B
void Fade::ImageGeneration(float scale) 
{
	if (m_newPunching == false) {			//�摜����������Ă��Ȃ��Ƃ��B
		//�g��k����������摜�𐶐����鏈�����X�B
		m_spriteRenderPunching = NewGO<SpriteRender>(0, "spriternder");
		m_spriteRenderPunching->Init(L"Assets/sprite/fadePunching.dds", w, h);
		m_spriteRenderPunching->SetPosition(m_position);
		scalePunching = scale;
		m_scalePunching = { scalePunching,scalePunching,scalePunching };
		m_spriteRenderPunching->SetScale(m_scalePunching);
		m_spriteRenderPunching->SetRotation(m_rotation);
		m_newPunching = true;				//�摜���������ꂽ�̂Ńt���O��Ԃ��B
	}

	if (scalePunching <= 1.5f) {
		if (m_newCover == false) {				//�摜����������Ă��Ȃ��Ƃ��B
			//�J�o�[�摜�𐶐����鏈�����X�B
			m_spriteRenderCover = NewGO<SpriteRender>(0, "spriterender");
			m_spriteRenderCover->Init(L"Assets/sprite/fadeCover.dds", w, h);
			m_spriteRenderCover->SetPosition(m_position);
			m_scaleCover = { 1.f,1.f,1.f };
			m_spriteRenderCover->SetScale(m_scaleCover);
			m_spriteRenderCover->SetRotation(m_rotation);
			m_newCover = true;					//�摜���������ꂽ�̂Ńt���O��Ԃ��B
		}
	}
}

//�t�F�[�h�C������B
void Fade::FadeIn()
{
	m_fadeState = enFadeIn;					//��Ԃ�FadeIn�ɕύX����B
//	ImageGeneration(0.1f);
	scalePunching += 10.f* gametime().GetFrameDeltaTime();
	m_scalePunching = { scalePunching,scalePunching,scalePunching };
	m_spriteRenderPunching->SetScale(m_scalePunching);
	if (scalePunching >= 1.f) {
		DeleteGO(m_spriteRenderCover);
	}
}

//�t�F�[�h�A�E�g����B
void Fade::FadeOut()
{
	if (scalePunching <= fadeOutSizeLimit) {
		return;
	}
	m_fadeState = enFadeOut;				//��Ԃ�FadeOut�ɕύX����B
	ImageGeneration(10.f);					//�摜��ύX����B
	//�摜�̃X�P�[�����k������B
	scalePunching -= 10.f* gametime().GetFrameDeltaTime();			
	m_scalePunching = { scalePunching,scalePunching,scalePunching };
	m_spriteRenderPunching->SetScale(m_scalePunching);
}

// �t�F�[�h�A�E�g��t�F�[�h�C������B
void Fade::PlayFade(/*float FadeInterval*/)
{
	if (m_fadeState != enFadeIn) {
		FadeOut();			//�t�F�[�h�A�E�g����B
	}

	if (scalePunching <= fadeOutSizeLimit) {
		interval += gametime().GetFrameDeltaTime();
	}

	if (/*scalePunching <= 0.1f*/interval >= 1.f /*|| m_fadeState == enFadeIn*/) {
		FadeIn();			//�t�F�[�h�C������B
		if (scalePunching >= 10.f) {
			DeleteGO(this);
		}
	}
}

void Fade::Update()
{
	PlayFade();

	//�摜����������Ă��Ȃ��Ƃ��A�������I������B
	if (!m_spriteRenderPunching) {		
		return;
	}
}