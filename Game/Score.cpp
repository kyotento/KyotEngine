#include "stdafx.h"
#include "Score.h"

namespace {
	float x = -565.f;			//画像のX座標。
	float y = -285.f;			//画像のY座標。

	float spriteScale = 150.f;	//画像のスケール。
}

Score::Score()
{
}

Score::~Score()
{
	DeleteGO(m_spriteRender);		//スキンモデルを消す。
}

bool Score::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "sprite");
	m_spriteRender->Init(L"Assets/sprite/coin.dds", spriteScale, spriteScale);			//初期化。　
	m_position2D.x = x;														//X座標を指定。
	m_position2D.y = y;														//Y座標を指定。
	m_spriteRender->SetPosition(m_position2D);								//座標を設定。

	m_fontPosition.x = m_position2D.x -= 25.f;			//フォントのX座標を指定。
	m_fontPosition.y = m_position2D.y += 30.f;			//フォントのY座標を指定。

	return true;
}

void Score::Update()
{
}

void Score::AfterFontRender()
{
	m_font.Begin();															//描画開始。
	wchar_t text[64];														//テキストに使う配列。
	swprintf_s(text, L"%01d", m_score);										//テキストを設定。
	m_font.Draw(text, m_fontPosition, m_fontColor, 0.0f, m_fontScale);		//更新処理。
	m_font.End();															//描画終了。
}