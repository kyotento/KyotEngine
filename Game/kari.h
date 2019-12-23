#pragma once
#include "GameObject.h"

class kari : public GameObject
{
public:
	kari();
	~kari();

	bool Start();
	void Update();

private:

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();

	SpriteRender*m_spriteRender = nullptr;

};

