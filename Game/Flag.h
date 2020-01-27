#pragma once
#include "GameObject.h"

class Flag : public GameObject
{
public:
	Flag();
	~Flag();

	bool Start();
	void Update();
	
	/// <summary>
	/// 座標を指定する。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// スケールを指定する。
	/// </summary>
	/// <param name="scale">スケール</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// 回転を指定。
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

private:

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::Zero();					//スケール。

	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	SkinModelRender* m_skinModelRender = nullptr;			//モデル生成。

};

