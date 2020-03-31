#include "stdafx.h"
#include "StageSelectDetailed.h"

namespace {
	static const float width = 480.f;			//�摜�̕��B
	static const float height = 320.f;			//�摜�̍����B
}

StageSelectDetailed::StageSelectDetailed()
{
}


StageSelectDetailed::~StageSelectDetailed()
{
	if (m_spriteRender != nullptr) {
		DeleteGO(m_spriteRender);
	}
}

bool StageSelectDetailed::Start()
{


	return true;
}

//�X�e�[�W�̏ڍ׉摜�𐶐����鏈���B
void StageSelectDetailed::NewDetailedImage(int stageNum)
{
	if (m_newImage == false) {			//�摜����������Ă��Ȃ��Ƃ��B

		m_spriteRender = NewGO<SpriteRender>(0, "spriteredner");

		//�܂��Ȃ����Q�ƂR�����B
		if (stageNum == 0) {
			m_spriteRender->Init(L"Assets/sprite/Stage1.dds", width, height);
		}
		if (stageNum == 1) {
			m_spriteRender->Init(L"Assets/sprite/Stage2.dds", width, height);
		}
		if (stageNum == 2) {
			m_spriteRender->Init(L"Assets/sprite/Stage3.dds", width, height);
		}
		m_newImage = true;
	}

}

//�ڍ׉摜�����������B
void StageSelectDetailed::DeleteDetailedImage()
{
	//�摜����������Ă���Ƃ��摜�����������B
	if (m_newImage) {
		DeleteGO(m_spriteRender);	
		m_newImage = false;
	}
}

void StageSelectDetailed::Update()
{
	m_position.x = 360.f;
	m_position.y = 180.f;

	if (m_spriteRender != nullptr) {
		m_spriteRender->SetPosition(m_position);
		m_spriteRender->SetScale(m_scale);
		m_spriteRender->SetRotation(m_rotation);
	}
}
