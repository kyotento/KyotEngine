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
	/// ���M�̏�ԁB
	/// </summary>
	enum DishState
	{
		endefault,				//���ꂢ�Ȃ��M�B
		endirty,				//����Ă�B
		enSomethingOnBoard,		//��������Ă���Ƃ��B
	};

	/// <summary>
	/// ���M�̏�Ԃ��Z�b�g���鏈���B
	/// </summary>
	/// <param name="dishState">���M�̏��</param>
	void SetState(DishState dishState)
	{
		m_dishState = static_cast<DishState>(dishState);
	}

	/// <summary>
	/// ���M�̏�Ԃ��擾����B
	/// </summary>
	/// <returns>���M�̍��W</returns>
	int GetState()
	{
		return m_dishState;
	}

private:


	DishState m_dishState = endefault;			//���M�̏�ԁB


};

