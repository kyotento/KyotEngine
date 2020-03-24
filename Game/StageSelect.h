#pragma once
#include "level/Level.h"
#include "GameObject.h"
#include "Flag.h"
#include "Bus.h"
#include "Bridge.h"
#include "River.h"

class StageSelect : public GameObject
{
public:
	StageSelect();
	~StageSelect();

	bool Start();

	void Update();


private:

	Flag* m_flag = nullptr;					//���B
	Bus* m_bus = nullptr;					//�o�X�B
	Bridge* m_bridge = nullptr;				//���B
	River* m_river = nullptr;				//��B

	Level m_level;							//���x���B

};

