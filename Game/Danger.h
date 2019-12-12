#pragma once
#include "GameObject.h"

class Danger : public GameObject
{
public:
	Danger();
	~Danger();

	bool Start();
	void Update();

	/// <summary>
	/// 座標を指定。
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

