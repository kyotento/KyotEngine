#pragma once
#include "GameObject.h"

class Score : public GameObject
{
public:
	Score();
	~Score();

	bool Start();
	void Update();

private:

	CVector3 m_position2D = CVector3::Zero();			//2D�̍��W�B	
	CVector3 m_scale2D = CVector3::One();				//2D�̃X�P�[���B

	SpriteRender* m_spriteRender = nullptr;			//2D�`��N���X�B


};

