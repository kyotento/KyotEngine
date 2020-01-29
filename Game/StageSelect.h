#pragma once
#include "level/Level.h"
#include "GameObject.h"
#include "Flag.h"
#include "Bus.h"
#include "Bridge.h"

class StageSelect : public GameObject
{
public:
	StageSelect();
	~StageSelect();

	bool Start();

	void Update();


private:

	Flag* m_flag = nullptr;					//旗。
	Bus* m_bus = nullptr;					//バス。
	Bridge* m_bridge = nullptr;				//橋。

	Level m_level;							//レベル。

};

