/// <summary>
/// �X�e�[�W�P�B
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

	int m_dishNum = 0;								//�������ꂽ���M�̐��B
	static const int m_dishNumUpperLimit = 4;		//��������邨�M�̐�����B

};

