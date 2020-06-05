/// <summary>
/// チェックマーク２D。
/// </summary>
#pragma once
#include "GameObject.h"

class Check : public GameObject
{
public:
	Check();
	~Check();

	bool Start();
	void Update();

	/// <summary>
	/// 座標を指定する。
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

private:

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::One();						//拡大率。

	SkinModelRender* m_skinModelRender = nullptr;			//スキンモデル。

};

