/// <summary>
/// �t�H���g�����B
/// </summary>
#pragma once
class Font
{
public:
	Font();
	~Font();

private:

	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<�X�v���C�g�o�b�`�B
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<�X�v���C�g�t�H���g�B

};

