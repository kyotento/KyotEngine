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

	Flag* m_flag[3] = { nullptr,nullptr,nullptr };					//���B
	Bus* m_bus = nullptr;					//�o�X�B
	Bridge* m_bridge = nullptr;				//���B
	River* m_river = nullptr;				//��B
	StageSelectFloor* m_stageSelectFloor = nullptr;			//���B
	StageSelectDetailed* m_stageSelectDetailed = nullptr;	//�X�e�[�W�̏ڍ׉摜�G

	Level m_level;							//���x���B

};

