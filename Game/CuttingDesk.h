/// <summary>
/// まな板付きの机。
/// </summary>
#pragma once
#include "ObjectAbove.h"

class CuttingDesk : public ObjectAbove
{
public:
	CuttingDesk();
	~CuttingDesk();

	bool Start();
	void Update();


private:

};

