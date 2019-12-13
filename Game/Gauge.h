#pragma once

class Gauge : public GameObject
{
public:
	Gauge();
	~Gauge();

	bool Start();
	void Update();

	/// <summary>
	/// ゲージを拡大する。
	/// </summary>
	/// <param name="time">拡大時間</param>
	void Expansion(float time);

	/// <summary>
	/// ゲージの拡大処理
	/// </summary>
	/// <param name="time">拡大完了時間</param>
	/// <param name="numberOfTimes">拡大回数</param>
	void Magnification(float time, float numberOfTimes);

	/// <summary>
	/// ゲージのX軸拡大率。
	/// </summary>
	/// <returns>拡大率X軸</returns>
	float GetScale()
	{
		return m_x;
	}

	/// <summary>
	/// 座標を取得する。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// 座標を指定する。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ゲージの拡大率が最大かどうかを返す。
	/// </summary>
	/// <returns>拡大最大値フラグ</returns>
	bool GetGaugeMax()
	{
		return m_gaugeMax;
	}

	/// <summary>
	/// ゲージの拡大率を半分にする。
	/// </summary>
	void GaugeHalf()
	{
		m_x = m_x / 2;
	}

private:

	bool m_gaugeMax = false;							//ゲージの拡大率が最大のときtrueになる。

	float m_x = 0.0f;									//ゲージのX軸拡大率。
	float m_expansionTimer = 0.f;						//拡大処理に使うタイマー。

	CVector2 m_pivot = { 0.f,0.5f };					//基点。

	CVector3 m_position = {0,0,0};						//ゲージと基盤の座標。
	CVector3 m_scaleGauge = CVector3::One();			//ゲージの拡大率。

	//SpriteRender* m_spriteRender = nullptr;			//ゲージ基盤用スプライト。
	//SpriteRender* m_spriteRenderGauge = nullptr;		//ゲージ用スプライト。

	SkinModelRender* m_skinModelRender = nullptr;				//ゲージ基盤用スキンモデル。
	SkinModelRender* m_skinModelRenderGauge = nullptr;			//ゲージ用スキンモデル。

};

