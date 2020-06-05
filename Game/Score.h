/// <summary>
/// ゲームのスコア表示。
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
	/// フォントを描画する関数。
	/// </summary>
	void AfterFontRender();

	/// <summary>
	/// スコアを加算(減算)する関数。
	/// </summary>
	/// <param name="score">加算するスコア</param>
	void AddScore(int score)
	{
		m_score += score;
	}

	/// <summary>
	/// スコアを取得する。
	/// </summary>
	/// <returns>スコア</returns>
	int GetScore()
	{
		return m_score;
	}

	/// <summary>
	/// チップ加算前のスコアを加算する。
	/// </summary>
	/// <param name="profit">加算するスコア</param>
	void AddProfit(int profit)
	{
		m_profit += profit;
	}

	/// <summary>
	/// チップ加算前のスコアを取得する。
	/// </summary>
	/// <returns>チップ加算前のスコア</returns>
	int GetProfit()
	{
		return m_profit;
	}

	/// <summary>
	/// チップを加算する。
	/// </summary>
	/// <param name="chip">加算するチップ</param>
	void AddChip(int chip)
	{
		m_chip += chip;
	}

	/// <summary>
	/// チップを取得する。
	/// </summary>
	/// <returns></returns>
	int GetChip()
	{
		return m_chip;
	}

	/// <summary>
	/// ペナルティを加算する。
	/// </summary>
	/// <param name="penalty">加算するペナルティ</param>
	void AddPenalty(int penalty)
	{
		m_penalty += penalty;
	}

	/// <summary>
	/// ペナルティを取得する。
	/// </summary>
	/// <returns>ペナルティ</returns>
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

	int m_score = 0;									//スコア。
	int m_profit = 0;									//チップ加算前のスコア。
	int m_chip = 0;										//チップ。
	int m_penalty = 0;									//ペナルティ。

	int m_starOne = 0;									//星１のスコア。
	int m_starTwo = 0;									//星２のスコア。	
	int m_starThree = 0;								//星３のスコア。

	float m_fontScale = 1.5f;							//フォントのスケール。

	CVector2 m_fontPosition = CVector2::Zero();			//フォントの座標。

	CVector3 m_position2D = CVector3::Zero();			//2Dの座標。	
	CVector3 m_scale2D = CVector3::One();				//2Dのスケール。

	CVector4 m_fontColor = CVector4::Black;				//フォントの色。

	SpriteRender* m_spriteRender = nullptr;				//2D描画クラス。

	Font m_font;			//フォント。

};

