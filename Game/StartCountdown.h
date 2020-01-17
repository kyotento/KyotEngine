#pragma once
#include "GameObject.h"

class StartCountdown : public GameObject
{
public:
	StartCountdown();
	~StartCountdown();

	bool Start();
	void Update();

	/// <summary>
	/// スケールの更新処理。
	/// </summary>
	void ScaleUpdate();

	/// <summary>
	/// ゲームを進行するか否かを決めるフラグを変更する関数。
	/// </summary>
	/// <param name="gameStartFlag">ゲーム更新フラグ</param>
	void SetGameStartFlag(bool gameStartFlag)
	{
		m_gameStartFlag = gameStartFlag;
	}

	/// <summary>
	///	ゲームを振興するか否かを決めるフラグの状態を取得する関数。
	/// </summary>
	/// <returns>ゲーム更新フラグ</returns>
	bool GetGameStartFlag()
	{
		return m_gameStartFlag;
	}

private:

	float m_scale = 0.f;
	float m_deleteTimer = 0.f;								//画像を消すタイマー。

	bool m_newReady = false;								//Readyが生成されたか。
	bool m_newStart = false;								//Startが生成されたか。
	bool m_gameStartFlag = false;							//ステージスタートフラグ。

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_scaleReady = CVector3::Zero();				//Ready画像スケール。
	CVector3 m_scaleStart = CVector3::Zero();				//スタート画像。

	SpriteRender* m_spriteRenderReady = nullptr;			//Readyの画像を出すクラス。
	SpriteRender* m_spriteRenderStart = nullptr;			//スタートの画像を出すクラス。

};

