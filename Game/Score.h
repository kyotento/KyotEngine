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

	CVector3 m_position2D = CVector3::Zero();			//2Dの座標。	
	CVector3 m_scale2D = CVector3::One();				//2Dのスケール。

	SpriteRender* m_spriteRender = nullptr;			//2D描画クラス。


};

