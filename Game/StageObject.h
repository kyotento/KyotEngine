#pragma once

/// <summary>
///ステージ上に置かれるオブジェクトの基底クラス。 
/// </summary>

class StageObject : public GameObject
{
public:
	StageObject();
	~StageObject();

	bool Start();
	void Update();


protected:

	/// <summary>
	/// 座標指定。
	/// </summary>
	/// <param name="a">座標</param>
	void SetPosition(CVector3 a)
	{
		m_position = a;
	}

	/// <summary>
	/// 座標を持ってくる。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// スケール指定。
	/// </summary>
	/// <param name="a">スケール</param>
	void SetScale(CVector3 a)
	{
		m_scale = a;
	}

	/// <summary>
	/// スケールを持ってくる。
	/// </summary>
	/// <returns></returns>
	CVector3 GetScale()
	{
		return m_scale;
	}

	/// <summary>
	/// 回転を指定する。
	/// </summary>
	/// <param name="a">回転</param>
	void SetRotation(CQuaternion a)
	{
		m_rotation = a;
	}

	/// <summary>
	/// 回転を持ってくる。
	/// </summary>
	/// <returns>回転</returns>
	CQuaternion GetRotation()
	{
		return m_rotation;
	}

	SkinModelRender* m_skinModelRender = nullptr;				//すきんもでる。

private:

	CVector3 m_position = CVector3::Zero();						//座標。
	CVector3 m_scale = CVector3::One();							//スケール。

	CQuaternion m_rotation = CQuaternion::Identity();			//回転。



};

