#pragma once
#include "GameObject.h"

class Bus : public GameObject
{
public:
	Bus();
	~Bus();

	bool Start();
	void Update();

private:

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One()*5.f;

	CQuaternion m_rotation = CQuaternion::Identity();

	SkinModelRender* m_skinModelRender = nullptr;

};

