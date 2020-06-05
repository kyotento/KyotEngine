/// <summary>
/// 火事マーク2D。
/// </summary>
#pragma once
#include "GameObject.h"

class Fire : public GameObject
{
public:
	Fire();
	~Fire();

	bool Start();
	void Update();

	/// <summary>
	/// 座標を指定する関数。
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

private:

	CVector3 m_position = CVector3::Zero();				//座標。

	SkinModelRender* m_skinModelRender = nullptr;		//スキンモデル。

};

