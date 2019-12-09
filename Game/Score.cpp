#include "stdafx.h"
#include "Score.h"

namespace {
	float x = -540.f;			//画像のX座標。
	float y = -260.f;			//画像のY座標。
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
	m_spriteRender->Init(L"Assets/sprite/coin.dds", 200.f, 200.f);			//初期化。　
	m_position2D.x = x;														//X座標を指定。
	m_position2D.y = y;														//Y座標を指定。
	m_spriteRender->SetPosition(m_position2D);								//座標を設定。

	return true;
}

void Score::Update()
{

}