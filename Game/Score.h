/// <summary>
/// �Q�[���̃X�R�A�\���B
/// </summary>

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
	/// �t�H���g��`�悷��֐��B
	/// </summary>
	void AfterFontRender();

	/// <summary>
	/// �X�R�A�����Z(���Z)����֐��B
	/// </summary>
	/// <param name="score">���Z����X�R�A</param>
	void AddScore(int score)
	{
		m_score += score;
	}

	/// <summary>
	/// �X�R�A���擾����B
	/// </summary>
	/// <returns>�X�R�A</returns>
	int GetScore()
	{
		return m_score;
	}

	/// <summary>
	/// �`�b�v���Z�O�̃X�R�A�����Z����B
	/// </summary>
	/// <param name="profit">���Z����X�R�A</param>
	void AddProfit(int profit)
	{
		m_profit += profit;
	}

	/// <summary>
	/// �`�b�v���Z�O�̃X�R�A���擾����B
	/// </summary>
	/// <returns>�`�b�v���Z�O�̃X�R�A</returns>
	int GetProfit()
	{
		return m_profit;
	}

	/// <summary>
	/// �`�b�v�����Z����B
	/// </summary>
	/// <param name="chip">���Z����`�b�v</param>
	void AddChip(int chip)
	{
		m_chip += chip;
	}

	/// <summary>
	/// �`�b�v���擾����B
	/// </summary>
	/// <returns></returns>
	int GetChip()
	{
		return m_chip;
	}

	/// <summary>
	/// �y�i���e�B�����Z����B
	/// </summary>
	/// <param name="penalty">���Z����y�i���e�B</param>
	void AddPenalty(int penalty)
	{
		m_penalty += penalty;
	}

	/// <summary>
	/// �y�i���e�B���擾����B
	/// </summary>
	/// <returns>�y�i���e�B</returns>
	int GetPenalty()
	{
		return m_penalty;
	}

	int GetStarOne()
	{
		return m_starOne;
	}

	int GetStarTwo()
	{
		return m_starTwo;
	}

	int GetStarThree()
	{
		return m_starThree;
	}

private:

	int m_score = 0;									//�X�R�A�B
	int m_profit = 0;									//�`�b�v���Z�O�̃X�R�A�B
	int m_chip = 0;										//�`�b�v�B
	int m_penalty = 0;									//�y�i���e�B�B

	int m_starOne = 0;									//���P�̃X�R�A�B
	int m_starTwo = 0;									//���Q�̃X�R�A�B	
	int m_starThree = 0;								//���R�̃X�R�A�B

	float m_fontScale = 1.5f;							//�t�H���g�̃X�P�[���B

	CVector2 m_fontPosition = CVector2::Zero();			//�t�H���g�̍��W�B

	CVector3 m_position2D = CVector3::Zero();			//2D�̍��W�B	
	CVector3 m_scale2D = CVector3::One();				//2D�̃X�P�[���B

	CVector4 m_fontColor = CVector4::Black;				//�t�H���g�̐F�B

	SpriteRender* m_spriteRender = nullptr;				//2D�`��N���X�B

	Font m_font;			//�t�H���g�B

};

