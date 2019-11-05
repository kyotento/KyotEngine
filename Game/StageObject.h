#pragma once
#include "physics/PhysicsStaticObject.h"

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

protected:

	SkinModelRender* m_skinModelRender = nullptr;				//すきんもでる。
	SkinModelRender* m_skinModelRenderCollidion = nullptr;		//すきんもでる(当たり判定用ボックス限定)。

	CVector3 m_position = CVector3::Zero();						//座標。
	CVector3 m_scale = CVector3::One();							//スケール。

	CQuaternion m_rotation = CQuaternion::Identity();			//回転。

	PhysicsStaticObject m_physicsStaticObject;					//静的物理オブジェクト。
																			/*
																				1.Desk
																				2.Delivery
																				3.DishHold
																				4.DustBox
																				5.GasStove
																				6.Kitchen
																				7.OnionBox
																				8.TomatoBox
																				9.CuttingDesk

																			*/


private:





};

