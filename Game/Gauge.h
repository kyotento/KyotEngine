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
	void Expansion();

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

private:

	float m_x = 0.0f;									//ゲージのX軸拡大率。

	CVector2 m_pivot = { 0.5f,0.5f };					//基点。

	CVector3 m_position = {0,0,0}/* CVector3::Zero()*/;				//ゲージと基盤の座標。
	CVector3 m_scaleGauge = CVector3::Zero();			//ゲージの拡大率。

	SpriteRender* m_spriteRender = nullptr;				//ゲージ基盤用スプライト。
	SpriteRender* m_spriteRenderGauge = nullptr;		//ゲージ用スプライト。


};

