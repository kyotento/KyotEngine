/// <summary>
/// フォント生成。
/// </summary>
#pragma once
class Font
{
public:
	Font();
	~Font();

private:

	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<スプライトバッチ。
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<スプライトフォント。

};

