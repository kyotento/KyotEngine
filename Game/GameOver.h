/// <summary>
/// ゲームオーバークラス。
/// </summary>
#pragma once
#include "GameOver.h"
#include "Result.h"

class GameOver : public GameObject
{
public:
	GameOver();
	~GameOver();

	bool Start();
	void Update();

	/// <summary>
	/// ゲームでせいせいされたものを消す。
	/// </summary>
	void DeleteField();

	/// <summary>
	/// スケールの更新処理。
	/// </summary>
	void ScaleUpdate();

private:

	float m_scalefloat = 0.f;						//スケール更新用。
	float m_timer = 0.f;							//画像を消すタイマー。

	CVector3 m_position = CVector3::Zero();			//座標。
	CVector3 m_scale = CVector3::Zero();			//スケール。

	SpriteRender* m_spriteRender = nullptr;			//画像生成クラス。

	Result* m_result = nullptr;						//リザルト。

};

