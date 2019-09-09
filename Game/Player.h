#pragma once

class Player : public GameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

private:

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::One();						//拡大率。

	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	SkinModelRender* m_skinModelRender = nullptr;			//スキンモデル。

};

