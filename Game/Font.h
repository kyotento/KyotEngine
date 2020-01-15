/// <summary>
/// �t�H���g�����B
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
	/// �t�H���g��ݒ肷��
	/// </summary>
	/// <param name="font">�t�H���g</param>
	void SetFont(DirectX::SpriteFont* font)
	{
		m_spriteFont = font;
	}

	/// <summary>
	/// �`��J�n�B
	/// </summary>
	/// <param name="rt">�����_�[�R���e�L�X�g</param>
	void Begin(RenderContext& rc);

	/// <summary>
	/// �`��I���B
	/// </summary>
	/// <param name="rt">�����_�[�R���e�L�X�g</param>
	void End(RenderContext& rc);

	/// <summary>
	/// �`�揈���B
	/// </summary>
	/// <param name="text">�\���������e�L�X�g</param>
	/// <param name="position">���W</param>
	/// <param name="color">�F</param>
	/// <param name="rotation">��]</param>
	/// <param name="scale">�X�P�[��</param>
	/// <param name="pivot">��_</param>
	void Draw(wchar_t const* text, const CVector2& position, const CVector4& color = CVector4::White(),
		float rotation = 0.0f, float scale = 1.0f, CVector2 pivot = { 0.5f,0.5f });

private:

	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<�X�v���C�g�o�b�`�B
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<�X�v���C�g�t�H���g�B
	CMatrix m_scaleMat;			//�g��s��B
};

