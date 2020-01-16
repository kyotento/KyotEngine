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
	/// スコアを加算(減算)する関数。
	/// </summary>
	/// <param name="score">加算するスコア</param>
	void AddScore(int score)
	{
		m_score += score;
	}

	/// <summary>
	/// フォントを描画する関数。
	/// </summary>
	void AfterFontRender();

private:

	int m_score = 0;									//スコア。

	float m_fontScale = 1.5f;							//フォントのスケール。

	CVector2 m_fontPosition = CVector2::Zero();			//フォントの座標。

	CVector3 m_position2D = CVector3::Zero();			//2Dの座標。	
	CVector3 m_scale2D = CVector3::One();				//2Dのスケール。

	CVector4 m_fontColor = CVector4::Black;				//フォントの色。

	SpriteRender* m_spriteRender = nullptr;				//2D描画クラス。

	Font m_font;			//フォント。

};

