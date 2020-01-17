#pragma once
#include "GameObject.h"

class Result : public GameObject
{
public:
	Result();
	~Result();

	bool Start();
	void Update();


private:

	static const int m_starNum = 3;

	CVector3 m_positionSheet = CVector3::Zero();															//�V�[�g�̍��W�B
	CVector3 m_positionStar[m_starNum] = { CVector3::Zero(),CVector3::Zero(),CVector3::Zero() };			//���̍��W�B
	CVector3 m_scaleSheet = CVector3::One();																//�V�[�g�̃X�P�[���B
	CVector3 m_scaleStar[m_starNum] = { CVector3::One(),CVector3::One(),CVector3::One() };					//���̃X�P�[���B

	SpriteRender* m_spriteRenderSheet = nullptr;					//�V�[�g�𐶐�����摜�����N���X�B
	SpriteRender* m_spriteRenderStar[m_starNum] = { nullptr };		//���𐶐�����摜�����N���X�B		

};

