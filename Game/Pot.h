/// <summary>
/// ����B
/// </summary>
#pragma once
#include "KitchenWare.h"
#include "SoupBase.h"

class Pot : public KitchenWare
{
public:
	Pot();
	~Pot();

	bool Start();
	void Update();

	void Kari();

private:

	SoupBase* m_soupBase = nullptr;			//�X�[�v�����B

};
