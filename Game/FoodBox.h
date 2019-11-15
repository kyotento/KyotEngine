#pragma once
#include "Tomato.h"
#include "Onion.h"
#include "Belongings.h"
#include "ObjectAbove.h"
/// <summary>
/// �H�ו�����̊��N���X�B
/// </summary>
class Tomato;
class Onion;
class Belongings;
class FoodBox : public ObjectAbove
{
public:
	FoodBox();
	~FoodBox();

	bool Start();
	void Update();

	/// <summary>
	/// �H�ו��𐶐��B
	/// </summary>
	void NewFood();

	/// <summary>
	/// ���W���w��B
	/// </summary>
	/// <param name="position">���W</param>
	void SetPositon(CVector3 position)
	{
		m_position = position;
	}


protected:

	Tomato* m_tomato = nullptr;
	Onion* m_onion = nullptr;
	Belongings* m_food = nullptr;

private:



};

