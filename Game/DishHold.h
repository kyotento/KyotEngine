#pragma once
#include "ObjectAbove.h"
#include "Dish.h"

class DishHold : public ObjectAbove
{

public:
	DishHold();
	~DishHold();

	bool Start();
	void Update();

	/// <summary>
	///�@����Ă��邨�M�̐����Ǘ�����֐��B
	/// </summary>
	void NumberOfDished();

	/// <summary>
	/// ���M�̐����擾����B
	/// </summary>
	/// <param name="dishNum">���M�̐�</param>
	void SetDishNum(int dishNum)
	{
		m_dishNum = dishNum;
	}

private:

	int m_dishNum = 0;			//����Ă��邨�M�̐��B
	int m_oldDishNum = 0;		//�P�t���[���O�ɍڂ��Ă������M�̐��B

	CVector3 m_dishPosition = CVector3::Zero();		//���M�̍��W�B

	Dish* m_dish = nullptr;			//���M�B

};

