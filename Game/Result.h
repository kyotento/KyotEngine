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

	CVector3 m_positionSheet = CVector3::Zero();															//シートの座標。
	CVector3 m_positionStar[m_starNum] = { CVector3::Zero(),CVector3::Zero(),CVector3::Zero() };			//星の座標。
	CVector3 m_scaleSheet = CVector3::One();																//シートのスケール。
	CVector3 m_scaleStar[m_starNum] = { CVector3::One(),CVector3::One(),CVector3::One() };					//星のスケール。

	SpriteRender* m_spriteRenderSheet = nullptr;					//シートを生成する画像生成クラス。
	SpriteRender* m_spriteRenderStar[m_starNum] = { nullptr };		//星を生成する画像生成クラス。		

};

