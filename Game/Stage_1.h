/// <summary>
/// ステージ１。
/// </summary>
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

	int m_dishNum = 0;								//生成されたお皿の数。
	static const int m_dishNumUpperLimit = 4;		//生成されるお皿の数上限。

};

