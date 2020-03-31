#include "stdafx.h"
#include "StageSelectDetailed.h"

namespace {
	static const float width = 480.f;			//画像の幅。
	static const float height = 320.f;			//画像の高さ。
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

//ステージの詳細画像を生成する処理。
void StageSelectDetailed::NewDetailedImage(int stageNum)
{
	if (m_newImage == false) {			//画像が生成されていないとき。

		m_spriteRender = NewGO<SpriteRender>(0, "spriteredner");

		//まだないが２と３もやる。
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

//詳細画像を消す処理。
void StageSelectDetailed::DeleteDetailedImage()
{
	//画像が生成されているとき画像を消す処理。
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
