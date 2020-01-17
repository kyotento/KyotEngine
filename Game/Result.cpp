#include "stdafx.h"
#include "Result.h"
namespace {
	float m_sheet_w = 360.f;				//シートの画像の幅。
	float m_sheet_h = 540.f;				//シートの画像の高さ。
	float m_star_w = 80.f;					//星の画像の幅。
	float m_star_h = 80.f;					//星の画像の高さ。

}

//todo マジックナンバーはすべて仮。

Result::Result()
{
}


Result::~Result()
{
	if (m_spriteRenderSheet != nullptr) {				//シートが生成されているとき。
		DeleteGO(m_spriteRenderSheet);					//シートを消す。
	}
	for (int i = 0; i < m_starNum; i++) {				//星の配列分ループする。
		if (m_spriteRenderStar[i] != nullptr) {			//星が生成されていたら。
			DeleteGO(m_spriteRenderStar[i]);			//星を消す。
			m_spriteRenderStar[i] = nullptr;			//インスタンスを破棄。
		}
	}
}


bool Result::Start()
{

	m_spriteRenderSheet = NewGO<SpriteRender>(0, "sprite");										//スプライトクラスを生成。
	m_spriteRenderSheet->Init(L"Assets/sprite/result_sheet.dds", m_sheet_w, m_sheet_h);			//シートの初期化。
	m_spriteRenderSheet->SetPosition(m_positionSheet);											//座標を初期化。
	m_spriteRenderSheet->SetScale(m_scaleSheet);												//スケールを初期化。

	m_positionStar[0] = m_positionSheet;			//一つ目の星の座標にシートの座標を代入。
	m_positionStar[0].x -= 80.f;					//左に移動する。
	m_positionStar[0].y -= 90.f;					//下に移動する。

	for (int i = 0; i < m_starNum; i++) {			//生成する星の数分ループする。
		m_spriteRenderStar[i] = NewGO<SpriteRender>(1, "sprite");								//スプライトクラスを生成。
		m_spriteRenderStar[i]->Init(L"Assets/sprite/black_star.dds", m_star_w, m_star_h);		//星の初期化(はじめは黒い星)。
		m_spriteRenderStar[i]->SetPosition(m_positionStar[i]);									//座標を初期化。
		m_spriteRenderStar[i]->SetScale(m_scaleStar[i]);										//スケールを初期化。

		if (i <= m_starNum - 1) {					//次の配列が存在したら。
			m_positionStar[i + 1] = m_positionStar[i];											//次の星の座標に前の星の座標を代入。
			m_positionStar[i + 1].x += 80.f;													//右に移動する。
		}
	}

	return true;
}


void Result::Update()
{

}