#pragma once
#include "level/Level.h"

/// <summary>
/// フィールドの基底クラス。
/// </summary>
class StageBase : public GameObject
{
public:
	StageBase();
	~StageBase();

	bool Start();
	void Update();

protected:

	Level m_level;				//レベル。

private:

};

