#pragma once
#include "level/Level.h"
#include "GameObject.h"
#include "Flag.h"

class StageSelect : public GameObject
{
public:
	StageSelect();
	~StageSelect();

	bool Start();

	void Update();


private:

	Flag* m_flag = nullptr;					//���B

	Level m_level;							//���x���B

};

