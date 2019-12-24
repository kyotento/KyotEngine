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
	/// ゲージの状態。
	/// </summary>
	enum GaugeState
	{
		en66Then,		//６６％以上のとき。	
		en33Then,		//３３％以上のとき。
		en10Then,		//１０％以上のとき。
		en10Less		//１０％未満のとき。
	};

private:

	CVector2 m_pivot = { 0.0f,0.5f };				//ピボット。

	CVector3 m_position = CVector3::Zero();			//座標。
	CVector3 m_scale = CVector3::One();				//スケール。

	GaugeState m_gaugeState = en66Then;				//ゲージの状態。
	GaugeState m_oldGaugeState = en66Then;			//1フレーム前のゲージの状態。

	SpriteRender* m_spriteRender = nullptr;			//画像描画用。


};

