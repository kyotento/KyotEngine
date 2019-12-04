#pragma once
#include "Belongings.h"
#include "Cuisine.h"

class Dish : public Belongings
{
public:
	Dish();
	~Dish();

	bool Start();
	void Update();

	/// <summary>
	/// �����̊Ǘ��B
	/// </summary>
	void PutDish(int FoodType);

	/// <summary>
	/// ��ԕω��ɂ�郂�f���̕ύX�B
	/// </summary>
	void DishModelChange();

	/// <summary>
	///	���M���X�g�ɓ�ڈȍ~�̂��M��ǉ����鏈���B
	/// </summary>
	void AddDishList();

	/// <summary>
	/// ���M���X�g�̂��M�����������B
	/// </summary>
	void DeleteDishList(Kitchen* kitchen);

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
	void SetDishState(DishState dishState)
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

	/// <summary>
	/// ���X�g�̂��M�̐����w�肷��B
	/// </summary>
	/// <param name="dishListNum"></param>
	void SetDishListNum(int dishListNum)
	{
		m_dishListNum = dishListNum;
	}

	/// <summary>
	/// ���X�g�̂��M�̐����擾����B
	/// </summary>
	/// <returns>���X�g�̂��M�̐�</returns>
	int GetDisListNum()
	{
		return m_dishListNum;
	}

private:

	int m_dishListNum = 0;						//���X�g�̂��M�̐��B

	DishState m_dishState = endefault;			//���M�̏�ԁB
	DishState m_oldDishState = endefault;		//���M�̏��(1�t���[���O)�B

	Cuisine* m_cuisine = nullptr;				//�������B
	Kitchen* m_kitchen = nullptr;				//���M�􂢏�B


	typedef std::list<SkinModelRender*>DishList;			//���M���d�˂邽�߂̃��X�g�B
	DishList m_dishList;									//���M���X�g�B

};

