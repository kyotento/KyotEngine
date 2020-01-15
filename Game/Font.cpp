#include "stdafx.h"
#include "Font.h"


Font::Font()
{
	m_spriteBatch = GraphicsEngine().GetSpriteBatch();
	m_spriteFont = GraphicsEngine().GetSpriteFont();
	auto& ge = GraphicsEngine();
	//�g��s����쐬�B
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

//�`��J�n�B
void Font::Begin(RenderContext& rc)
{
	rc.PushRenderState();			//�����_�����O�X�e�[�g��ޔ��B

	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		m_scaleMat
	);
}

//�`��I���B
void Font::End(RenderContext& rc) 
{
	m_spriteBatch->End();

	rc.PopRenderState(true);			//�����_�����O�X�e�[�g�𕜊��I�I�B
}

//�`�揈���B
void Font::Draw(wchar_t const* text,const CVector2& position,
	const CVector4& color,float rotation,float scale,CVector2 pivot)
{
	if (text == nullptr) {			//��������������Ă��Ȃ��������ꍇ�B
		return;						//���������Ȃ��B
	}

	pivot.y = 1.f - pivot.y;		//��_�̌v�Z�B

	//���W�n��Sprite�ƍ��킹��B
	CVector2 pos = position;		//�摜�̍��W�B
	float frameBufferHalfW = SCREENWIDTH_W;			//2D�̕��𔼕��ɁB
	float frameBufferHalfH = SCREENHEIGHT_H;		//2D�̍����𔼕��ɁB
	//���W�ɑ���B
	pos.x += frameBufferHalfW;
	pos.y = -pos.y + frameBufferHalfH;

	//�`��I�B
	m_spriteFont->DrawString(
		m_spriteBatch,								//�X�v���C�g�o�b�`�B
		text,										//�`�悷�镶���B
		pos.vec,									//���W�B
		color,										//�F�B
		rotation,									//��]�B
		DirectX::XMFLOAT2(pivot.x, pivot.y),		//��_�B
		scale										//�X�P�[���B
	);

}