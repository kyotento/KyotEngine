#pragma once
#include "ObjectAbove.h"
#include "DishDirty.h"
#include "Dish.h"

class Kitchen : public ObjectAbove
{
public:
	Kitchen();
	~Kitchen();

	bool Start();
	void Update();

	/// <summary>
	/// ���M��􂤊֐��B
	/// </summary>
	void DishWashing();

	/// <summary>
	/// ���M�̃C���X�^���X����������B
	/// </summary>
	void DeleteDishInstance();

	/// <summary>
	/// �O�����牘�ꂽ���M�̃C���X�^���X��ݒ肷��֐��B
	/// </summary>
	/// <param name="dishDirty">���M�̃C���X�^���X</param>
	void SetDishDirtyInstance(DishDirty* dishDirty)
	{
		m_dishDirty = dishDirty;
	}


private:

	int m_timerK = 0;				//�J���J���̉��B

	Dish* m_dish = nullptr;						//���M�B
	DishDirty* m_dishDirty = nullptr;			//���ꂽ���M�B

};

