#pragma once
#include "GameObject.h"

class OrderSheet: public GameObject
{
public:
	OrderSheet();
	~OrderSheet();

	bool Start();
	void Update();

private:

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::One();						//スケール。

	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	SpriteRender* m_spriteRenderSheetNo1 = nullptr;			//画像生成クラス。一番奥のシート。
	SpriteRender* m_spriteRenderSheetNo2 = nullptr;			//画像生成クラス。手前のシート。

};

