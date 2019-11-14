#pragma once
#include "Belongings.h"
class Dish : public Belongings
{
public:
	Dish();
	~Dish();

	bool Start();
	void Update();

	/// <summary>
	/// ���M�̏�Ԃ��擾����B
	/// </summary>
	/// <returns>���M�̏��</returns>
	int GetState()
	{
		return m_dishState;
	}

private:

	/// <summary>
	/// ���M�̏�ԁB
	/// </summary>
	enum DishState
	{
		endefault,				//���ꂢ�Ȃ��M�B
		endirty,				//����Ă�B
		enSomethingOnBoard,		//��������Ă���Ƃ��B
	};

	DishState m_dishState = endefault;			//���M�̏�ԁB


};

