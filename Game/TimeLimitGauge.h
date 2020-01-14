#pragma once
#include "GameObject.h"

class TimeLimitGauge : public GameObject
{
public:
	TimeLimitGauge();
	~TimeLimitGauge();

	bool Start();
	void Update();

	/// <summary>
	/// 状態を変更する処理。
	/// </summary>
	void StateChange();

	/// <summary>
	/// モデルを変更する処理。
	/// </summary>
	void ModelChange();

	/// <summary>
	/// スケール変更。
	/// </summary>
	/// 120秒でスケールが0になる。
	void ChangeScale();

	/// <summary>
	/// スケール変更
	/// </summary>
	/// <param name="time">縮小時間</param>
	/// スケールが0になる時間を設定したい場合使用する。
	void ChangeScale(float time);

	/// <summary>
	/// 座標を設定する関数。
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

	/// <summary>
	/// 拡大率を設定する。
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// 拡大率を変えるX軸の
	/// </summary>
	/// <param name="scale_x">X軸の拡大率</param>
	void SetScale(int scale_x)
	{
		m_scale_x = scale_x;
	}

	/// <summary>
	/// X軸の拡大率を取得する。
	/// </summary>
	/// <returns>拡大率X</returns>
	float GetScale_X()
	{
		return m_scale_x;
	}
	
	/// <summary>
	/// ゲージの状態。
	/// </summary>
	enum GaugeState
	{
		en66Then,		//６６％以上のとき。	
		en33Then,		//３３％以上のとき。
		en10Then,		//１０％以上のとき。
		en10Less		//１０％未満のとき。
	};

	/// <summary>
	/// ゲージの状態を取得する。
	/// </summary>
	/// <returns>ゲージの状態</returns>
	int GetGaugeState()
	{
		return m_gaugeState;
	}

	/// <summary>
	/// タイムリミットフラグを取得する。
	/// </summary>
	/// <returns>タイムリミットフラグ</returns>
	bool GetTimeLimitFlag()
	{
		return m_timeLimitFlag;
	}

private:

	float m_scale_x = 1.f;							//拡大率X。

	bool m_timeLimitFlag = false;					//時間制限を超えたらtrueになる。(拡大率が0になったら)。

	CVector2 m_pivot = { 0.0f,0.5f };				//中心地。

	CVector3 m_position = CVector3::Zero();			//座標。
	CVector3 m_scale = CVector3::One();				//スケール。

	GaugeState m_gaugeState = en66Then;				//ゲージの状態。
	GaugeState m_oldGaugeState = en66Then;			//1フレーム前のゲージの状態。

	SpriteRender* m_spriteRender = nullptr;			//画像描画用。

};

