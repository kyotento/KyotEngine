/// <summary>
/// まな板。
/// </summary>
//todo おそらく使われないクラス。
#pragma once
#include "StageObject.h"
class CuttingBoard : public StageObject
{
public:
	CuttingBoard();
	~CuttingBoard();

	bool Start();
	void Update();


private:

};

