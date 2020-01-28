#include "stdafx.h"
#include "Fade.h"

//todo カバー画像なしでFadeを表現できるようにする。(現時点では仮)。

namespace {
	float w = 1280.f;					//画像の幅。
	float h = 720.f;					//画像の高さ。
	float scalePunching = 10.f;			//拡大縮小処理をする画像のスケール。
	float interval = 0.f;				//フェードアウトが完了してっからフェードイン開始までのラグ。
	float fadeOutSizeLimit = 0.3f;		//フェードアウト時の最小スケール。
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

//画像を生成する。
void Fade::ImageGeneration(float scale) 
{
	if (m_newPunching == false) {			//画像が生成されていないとき。
		//拡大縮小処理する画像を生成する処理諸々。
		m_spriteRenderPunching = NewGO<SpriteRender>(0, "spriternder");
		m_spriteRenderPunching->Init(L"Assets/sprite/fadePunching.dds", w, h);
		m_spriteRenderPunching->SetPosition(m_position);
		scalePunching = scale;
		m_scalePunching = { scalePunching,scalePunching,scalePunching };
		m_spriteRenderPunching->SetScale(m_scalePunching);
		m_spriteRenderPunching->SetRotation(m_rotation);
		m_newPunching = true;				//画像が生成されたのでフラグを返す。
	}

	if (scalePunching <= 1.5f) {
		if (m_newCover == false) {				//画像が生成されていないとき。
			//カバー画像を生成する処理諸々。
			m_spriteRenderCover = NewGO<SpriteRender>(0, "spriterender");
			m_spriteRenderCover->Init(L"Assets/sprite/fadeCover.dds", w, h);
			m_spriteRenderCover->SetPosition(m_position);
			m_scaleCover = { 1.f,1.f,1.f };
			m_spriteRenderCover->SetScale(m_scaleCover);
			m_spriteRenderCover->SetRotation(m_rotation);
			m_newCover = true;					//画像が生成されたのでフラグを返す。
		}
	}
}

//フェードインする。
void Fade::FadeIn()
{
	m_fadeState = enFadeIn;					//状態をFadeInに変更する。
//	ImageGeneration(0.1f);
	scalePunching += 10.f* gametime().GetFrameDeltaTime();
	m_scalePunching = { scalePunching,scalePunching,scalePunching };
	m_spriteRenderPunching->SetScale(m_scalePunching);
	if (scalePunching >= 1.f) {
		DeleteGO(m_spriteRenderCover);
	}
}

//フェードアウトする。
void Fade::FadeOut()
{
	if (scalePunching <= fadeOutSizeLimit) {
		return;
	}
	m_fadeState = enFadeOut;				//状態をFadeOutに変更する。
	ImageGeneration(10.f);					//画像を変更する。
	//画像のスケールを縮小する。
	scalePunching -= 10.f* gametime().GetFrameDeltaTime();			
	m_scalePunching = { scalePunching,scalePunching,scalePunching };
	m_spriteRenderPunching->SetScale(m_scalePunching);
}

// フェードアウト後フェードインする。
void Fade::PlayFade(/*float FadeInterval*/)
{
	if (m_fadeState != enFadeIn) {
		FadeOut();			//フェードアウトする。
	}

	if (scalePunching <= fadeOutSizeLimit) {
		interval += gametime().GetFrameDeltaTime();
	}

	if (/*scalePunching <= 0.1f*/interval >= 1.f /*|| m_fadeState == enFadeIn*/) {
		FadeIn();			//フェードインする。
		if (scalePunching >= 10.f) {
			DeleteGO(this);
		}
	}
}

void Fade::Update()
{
	PlayFade();

	//画像が生成されていないとき、処理を終了する。
	if (!m_spriteRenderPunching) {		
		return;
	}
}