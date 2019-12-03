/// <summary>
/// お鍋に何か入った時、スープを表現するためのクラス。
/// </summary>
#pragma once
#include "StageObject.h"
#include "Belongings.h"

class SoupBase : public StageObject
{
public:
	SoupBase();
	~SoupBase();

	bool Start();
	void Update();

	//座標を指定。
	CVector3 SetPositon(CVector3 pos)
	{
		m_position = pos;
	}

private:

//	CVector3 m_position = CVector3::Zero();		//座標。

};

