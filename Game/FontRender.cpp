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
	//�`��J�n�B
	m_font.Begin();

	const wchar_t* text = nullptr;			//�e�L�X�g�B
	if (m_text.c_str() != nullptr) {
		text = m_text.c_str();		//�擪�|�C���^�����B
	}

	//�`�揈���B
	m_font.Draw(
		text,				//�e�L�X�g�B
		m_position,			//���W�B
		m_color,			//�F�B
		m_rotation,			//��]�B
		m_scale,			//�X�P�[���B
		m_pivot				//��_�B
	);
	
	//�`��I���B
	m_font.End();
}