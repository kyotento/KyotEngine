#include "stdafx.h"
#include "Font.h"


Font::Font()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_spriteFont = g_graphicsEngine->GetSpriteFont();
	auto& ge = g_graphicsEngine;
	//拡大行列を作成。
	m_scaleMat.MakeScaling(
		{
			FRAME_BUFFER_W / static_cast<float>(SCREENWIDTH_W),		
			FRAME_BUFFER_H / static_cast<float>(SCREENHEIGHT_H),		
			1.0f
		}
	);
}


Font::~Font()
{
}

//描画開始。
void Font::Begin()
{
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		m_scaleMat
	);
}

//描画終了。
void Font::End() 
{
	m_spriteBatch->End();
}

//描画処理。
void Font::Draw(wchar_t const* text,const CVector2& position,
	const CVector4& color,float rotation,float scale,CVector2 pivot)
{
	if (text == nullptr) {			//もし何も書かれていないかった場合。
		return;						//何もかかない。
	}

	pivot.y = 1.f - pivot.y;		//基点の計算。

	//座標系をSpriteと合わせる。
	CVector2 pos = position;		//画像の座標。
	float frameBufferHalfW = SCREENWIDTH_W * 0.5f;			//2Dの幅を半分に。
	float frameBufferHalfH = SCREENHEIGHT_H * 0.5f;		//2Dの高さを半分に。
	//座標に代入。
	pos.x += frameBufferHalfW;
	pos.y = -pos.y + frameBufferHalfH;

	//描画！。
	m_spriteFont->DrawString(
		m_spriteBatch,								//スプライトバッチ。
		text,										//描画する文字。
		pos.vec,									//座標。
		color,										//色。
		rotation,									//回転。
		DirectX::XMFLOAT2(pivot.x, pivot.y),		//基点。
		scale										//スケール。
	);

}