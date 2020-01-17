#pragma once
#include "GameObject.h"
#include "StartCountdown.h"
#include "GameOver.h"

class Timer : public GameObject
{
public:
	Timer();
	~Timer();

	bool Start();
	void Update();

	/// <summary>
	/// 制限時間を00:00と表示するための計算処理。
	/// </summary>
	void UnitChange();

	/// <summary>
	///	フォントを描画するための関数。
	/// </summary>
	void AfterFontRender();

private:

	int m_second = 0;				//秒。
	int m_minute = 0;				//分。

	float m_timer = 30.f;			//タイマー。
	float m_fontScale = 1.5f;		//フォントのスケール。

	CVector2 m_fontPosition = CVector2::Zero();					//フォントの座標。

	CVector3 m_position2D = CVector3::Zero();					//2Dの座標。
	CVector3 m_scale2D = CVector3::Zero();						//2Dのスケール。

	CVector4 m_fontColor = CVector4::Black;					//フォントの色。

	CQuaternion m_quaternion2D = CQuaternion::Identity();		//2Dの回転。

	SpriteRender* m_spriteRender = nullptr;			//2Dを描画するためのクラス。
	FontRender* m_fontRender = nullptr;				//フォントを描画するためのクラス。
	StartCountdown* m_startCountDown = nullptr;		//ゲーム開始前の処理。
	GameOver* m_gameOver = nullptr;			//ゲーム終了クラス。

	Font m_font;			//フォントクラス。


};

