#include "stdafx.h"
#include "FontRender.h"


FontRender::FontRender()
{
}


FontRender::~FontRender()
{
}

void FontRender::PostRender()
{
	//描画開始。
	m_font.Begin();

	const wchar_t* text = nullptr;			//テキスト。
	if (m_text.c_str() != nullptr) {
		text = m_text.c_str();		//先頭ポインタを代入。
	}

	//描画処理。
	m_font.Draw(
		text,				//テキスト。
		m_position,			//座標。
		m_color,			//色。
		m_rotation,			//回転。
		m_scale,			//スケール。
		m_pivot				//基点。
	);
	
	//描画終了。
	m_font.End();
}