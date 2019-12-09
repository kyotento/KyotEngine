#pragma once
#include "GameObject.h"

class Timer : public GameObject
{
public:
	Timer();
	~Timer();

	bool Start();
	void Update();

private:

	float m_timer = 200.f;			//タイマー。

	CVector3 m_position2D = CVector3::Zero();					//2Dの座標。
	CVector3 m_scale2D = CVector3::Zero();						//2Dのスケール。
	CQuaternion m_quaternion2D = CQuaternion::Identity();		//2Dの回転。

	SpriteRender* m_spriteRender = nullptr;			//2Dを描画するためのクラス。

};

