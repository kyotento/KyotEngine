#pragma once
#include "physics/PhysicsStaticObject.h"
#include "StageObject.h"

class StageFloor : public StageObject
{
public:
	StageFloor();
	~StageFloor();

	bool Start();
	
	/// <summary>
	/// ステージの床を生成する処理。
	/// </summary>
	/// <param name="stageNum">ステージ番号</param>
	void NewSelectFloor(int stageNum);


private:

};

