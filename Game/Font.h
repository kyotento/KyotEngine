/// <summary>
/// フォント生成。
/// </summary>
/// 
#include "RenderContext.h"
#pragma once
class Font
{
public:
	Font();
	~Font();

	/// <summary>
	/// フォントを設定する
	/// </summary>
	/// <param name="font">フォント</param>
	void SetFont(DirectX::SpriteFont* font)
	{
		m_spriteFont = font;
	}

	/// <summary>
	/// 描画開始。
	/// </summary>
	/// <param name="rt">レンダーコンテキスト</param>
	void Begin(RenderContext& rc);

	/// <summary>
	/// 描画終了。
	/// </summary>
	/// <param name="rt">レンダーコンテキスト</param>
	void End(RenderContext& rc);

	/// <summary>
	/// 描画処理。
	/// </summary>
	/// <param name="text">表示したいテキスト</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="rotation">回転</param>
	/// <param name="scale">スケール</param>
	/// <param name="pivot">基点</param>
	void Draw(wchar_t const* text, const CVector2& position, const CVector4& color = CVector4::White(),
		float rotation = 0.0f, float scale = 1.0f, CVector2 pivot = { 0.5f,0.5f });

private:

	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<スプライトバッチ。
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<スプライトフォント。
	CMatrix m_scaleMat;			//拡大行列。
};

