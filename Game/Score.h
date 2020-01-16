#pragma once
#include "GameObject.h"

class Score : public GameObject
{
public:
	Score();
	~Score();

	bool Start();
	void Update();

	/// <summary>
	/// �X�R�A�����Z(���Z)����֐��B
	/// </summary>
	/// <param name="score">���Z����X�R�A</param>
	void AddScore(int score)
	{
		m_score += score;
	}

	/// <summary>
	/// �t�H���g��`�悷��֐��B
	/// </summary>
	void AfterFontRender();

private:

	int m_score = 0;									//�X�R�A�B

	float m_fontScale = 1.5f;							//�t�H���g�̃X�P�[���B

	CVector2 m_fontPosition = CVector2::Zero();			//�t�H���g�̍��W�B

	CVector3 m_position2D = CVector3::Zero();			//2D�̍��W�B	
	CVector3 m_scale2D = CVector3::One();				//2D�̃X�P�[���B

	CVector4 m_fontColor = CVector4::Black;				//�t�H���g�̐F�B

	SpriteRender* m_spriteRender = nullptr;				//2D�`��N���X�B

	Font m_font;			//�t�H���g�B

};

