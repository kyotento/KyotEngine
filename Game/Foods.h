/// <summary>
/// 食べ物の基底クラス。
/// </summary>
#pragma once
#include "Belongings.h"

class Foods : public Belongings
{
public:
	Foods();
	~Foods();

protected:

	bool m_CuttingModel = false;			//切られたモデルになっているか。


private:



};

