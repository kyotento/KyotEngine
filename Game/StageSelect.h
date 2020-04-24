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

	Flag* m_flag[3] = { nullptr,nullptr,nullptr };					//旗。
	Bus* m_bus = nullptr;					//バス。
	Bridge* m_bridge = nullptr;				//橋。
	River* m_river = nullptr;				//川。
	StageSelectFloor* m_stageSelectFloor = nullptr;			//床。
	StageSelectDetailed* m_stageSelectDetailed = nullptr;	//ステージの詳細画像；

	Level m_level;							//レベル。

};

