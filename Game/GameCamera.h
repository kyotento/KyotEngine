#pragma once
#include "GameObject.h"

class GameCamera : public GameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();

	/// <summary>
	/// カメラの始点、注視点をリセットする。
	/// </summary>
	void CameraReset();

	/// <summary>
	/// 座標を指定。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
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
	/// ターゲットを指定する。
	/// </summary>
	/// <param name="target">ターゲット</param>
	void SetTarget(CVector3 target)
	{
		m_target = target;
	}

	/// <summary>
	/// ターゲットを取得する。
	/// </summary>
	/// <returns>ターゲット</returns>
	CVector3 GetTarget()
	{
		return m_target;
	}

	/// <summary>
	/// 回転を指定する。
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// 回転を取得する。
	/// </summary>
	/// <returns>回転</returns>
	CQuaternion GetRotation()
	{
		return m_rotation;
	}

private:

	float m_near = 10.f;									//近平面。
	float m_far = 10000.f;									//遠平面。

	CVector3 m_position = { 0.0f, 900.0f, -600.0f };		//カメラの座標。
	CVector3 m_target = CVector3::Zero();					//ターゲットの座標。

	CQuaternion m_rotation = CQuaternion::Identity();		//カメラの回転。


};

