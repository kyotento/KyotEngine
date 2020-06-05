/// <summary>
/// ������񋟂���Ƃ���B
/// </summary>
#pragma once
#include "ObjectAbove.h"
#include "DishHold.h"
#include "OrderGenerations.h"

class Delivery : public ObjectAbove
{
public:
	Delivery();
	~Delivery();

	bool Start();
	void Update();

	int GetDishNum()
	{
		return m_DishNum3;
	}

	/// <summary>
	/// ���M�u���̃C���X�^���X���擾����B
	/// </summary>
	/// <param name="dishHold">���M�u��</param>
	void SetDishHold(DishHold* dishHold)
	{
		m_dishHold = dishHold;
	}


private:

	int m_DishNum3 = 0;			//�[�i���ꂽ���M�̐��B

	float m_StateChangeTime = 0.f;

	bool m_TimeAdvanced = false;
	bool GetDishTimingFlag = false;				//���M�̏�Ԃ��󂯎��^�C�~���O���w��B

	DishHold* m_dishHold = nullptr;

};

