/// <summary>
/// ����ɉ������������A�X�[�v��\�����邽�߂̃N���X�B
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

	//���W���w��B
	CVector3 SetPositon(CVector3 pos)
	{
		m_position = pos;
	}

private:

//	CVector3 m_position = CVector3::Zero();		//���W�B

};

