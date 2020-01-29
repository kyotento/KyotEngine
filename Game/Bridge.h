#pragma once
#include "GameObject.h"
#include "physics/PhysicsStaticObject.h"

class Bridge : public GameObject
{
public:
	Bridge();
	~Bridge();

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
	/// 回転を指定する。
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

private:

	CVector3 m_position = CVector3::Zero();						//座標。
	CVector3 m_scale = CVector3::One();							//スケール。

	CQuaternion m_rotation = CQuaternion::Identity();			//回転。

	SkinModelRender* m_skinModelRender = nullptr;				//スキンモデル。
	SkinModelRender* m_skinModelRenderCollidion = nullptr;		//当たり判定。
	PhysicsStaticObject m_physicsStaticObject;					//静的物理オブジェクト。

};

