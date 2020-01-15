#pragma once
#include "Font.h"

class FontRender
{
public:
	FontRender();
	~FontRender();

	/// <summary>
	/// �t�H���g��ݒ肷��B
	/// </summary>
	/// <param name="font">�t�H���g</param>
	void SetFont(DirectX::SpriteFont* font)
	{
		m_font.SetFont(font);
	}

	/// <summary>
	/// �e�L�X�g��ݒ�B
	/// </summary>
	/// <param name="text">������</param>
	/// <remarks>
	/// ���t���[���ĂԂƂ߂���񂱂������B
	/// </remarks>
	void SetText(const wchar_t* text)
	{
		if (wcscmp(m_text.c_str(), text) != 0) {
			//�����񂪕ς�����B
			m_text = text;
		}
	}

	/// <summary>
	/// �t�H���g�̍��W���w�肷��B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(CVector2 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �t�H���g�̃X�P�[�����w�肷��B
	/// </summary>
	/// <param name="scale">�t�H���g�̃X�P�[��</param>
	void SetScale(int  scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// �t�H���g�̉�]���w�肷��
	/// </summary>
	/// <param name="rot">�t�H���g�̉�]</param>
	/// <remarks>
	/// �P�ʂ̓��W�A���B
	/// </remarks>
	void SetRotation(float rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// �t�H���g�̕`�揈���̗�����쐬
	/// </summary>
	/// <param name="rc">�����_�[�R���e�L�X�g</param>
	void PostRender(RenderContext& rc);

private:

	float m_rotation = 0.f;							//�t�H���g�̉�]�B(�P�ʂ̓��W�A��)�B
	float m_scale = 1.f;							//�t�H���g�̊g�嗦�B

	CVector2 m_position = CVector2::Zero();			//�t�H���g�̍��W�B
	CVector2 m_pivot = { 0.5f,0.5f };				//�t�H���g�̊�_�B

	CVector4 m_color = CVector4::White();			//�t�H���g�̐F�B

	std::wstring m_text;							//�e�L�X�g�B

	Font m_font;									//�t�H���g�B

};

