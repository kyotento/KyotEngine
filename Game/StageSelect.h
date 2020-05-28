#pragma once
#include "level/Level.h"
#include "GameObject.h"
#include "Flag.h"
#include "Bus.h"
#include "Bridge.h"
#include "River.h"
#include "StageSelectFloor.h"
#include "StageSelectDetailed.h"

class StageSelect : public GameObject
{
public:
	StageSelect();
	~StageSelect();

	bool Start();

	void Update();


private:

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::One();						//スケール。
	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	Flag* m_flag[3] = { nullptr,nullptr,nullptr };					//旗。
	Bus* m_bus = nullptr;					//バス。
	Bridge* m_bridge = nullptr;				//橋。
	River* m_river = nullptr;				//川。
	StageSelectFloor* m_stageSelectFloor = nullptr;			//床。
	StageSelectDetailed* m_stageSelectDetailed = nullptr;	//ステージの詳細画像；
	SpriteRender* m_spriteRender = nullptr;					//スプライト。
	Sound* m_sound = nullptr;								//BGM。

	Level m_level;							//レベル。

};

