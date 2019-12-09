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

	float m_timer = 200.f;			//�^�C�}�[�B

	CVector3 m_position2D = CVector3::Zero();					//2D�̍��W�B
	CVector3 m_scale2D = CVector3::Zero();						//2D�̃X�P�[���B
	CQuaternion m_quaternion2D = CQuaternion::Identity();		//2D�̉�]�B

	SpriteRender* m_spriteRender = nullptr;			//2D��`�悷�邽�߂̃N���X�B

};

