/// <summary>
/// �q���H���Ԃ��Ă���Ƃ���B(���ꂽ���M�u����)�B
/// </summary>
#pragma once
#include "ObjectAbove.h"
#include "Dish.h"
#include "DishDirty.h"

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
	/// ���M�̐���ݒ肷��B
	/// </summary>
	/// <param name="dishNum">���M�̐�</param>
	void SetDishNum(int dishNum)
	{
		m_dishNum = dishNum;
	}

	/// <summary>
	/// ���M�̐����擾����B
	/// </summary>
	/// <returns>���M�̐�</returns>
	int GetDishNum()
	{
		return m_dishNum;
	}

	/// <summary>
	/// ���ꂽ���M�̃C���X�^���X���擾����B
	/// </summary>
	/// <returns>���ꂽ���M�̃C���X�^���X</returns>
	DishDirty *GetDirtyDishInstance()
	{
		return m_dishDirty;
	}

private:

	int m_dishNum = 0;			//����Ă��邨�M�̐��B
	int m_oldDishNum = 0;		//�P�t���[���O�ɍڂ��Ă������M�̐��B

	CVector3 m_dishPosition = CVector3::Zero();		//���M�̍��W�B

	Dish* m_dish = nullptr;							//���M�B
	DishDirty* m_dishDirty = nullptr;				//���ꂽ���M�B

};

