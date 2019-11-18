/// <summary>
/// 料理クラス。
/// </summary>
#include "StageObject.h"
#pragma once

class Cuisine : public StageObject
{
public:
	Cuisine();
	~Cuisine();

	bool Start();
	void Update();

	//スープを生成する処理。
	void NewSoup();

private:


};

