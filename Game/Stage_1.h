#pragma once
#include "StageBase.h"
#include "StageObject.h"

class Stage_1 : public StageBase
{
public:
	Stage_1();
	~Stage_1();

	bool Start();
	void Update();

private:

	int m_dishNum = 0;								//¶¬‚³‚ê‚½‚¨M‚Ì”B
	static const int m_dishNumUpperLimit = 4;		//¶¬‚³‚ê‚é‚¨M‚Ì”ãŒÀB

};

