/// <summary>
/// ����B
/// </summary>
#pragma once
#include "Belongings.h"
#include "SoupBase.h"
#include "Gauge.h"

class Pot : public Belongings
{
public:
	Pot();
	~Pot();

	bool Start();
	void Update();

	/// <summary>
	/// �X�[�v���������ꂽ���̏���
	/// </summary>
	void Soup();

	/// <summary>
	/// �X�[�v�����������B
	/// </summary>
	void DeleteLikeSoup();

	/// <summary>
	/// ���M�ɓ����Ă���H�ו��̎�ނ�ݒ肷��B
	/// </summary>
	/// <param name="FoodType"></param>
	void SetPutSoupFoods(int FoodType)
	{
		m_putSoupFoods = FoodType;
	}

	/// <summary>
	/// ����ɓ����Ă���H�ו��̎�ނ���������B
	/// </summary>
	/// <returns>����ɓ����Ă���H�ו��̎��</returns>
	int GetPutSoupFoods()
	{
		return m_putSoupFoods;
	}

private:

	int m_putSoupFoods = 0;			//����ɓ����Ă���H�ו��̎�ށB

	CVector3 m_soupPos = CVector3::Zero();			//�X�[�v�̍��W�B
	CVector3 m_gaugePos = CVector3::Zero();			//�Q�[�W�̍��W�B


	SoupBase* m_soupBase = nullptr;			//�X�[�v�����B
	Gauge* m_gauge = nullptr;				//�Q�[�W�B
	Belongings* m_food = nullptr;			//�H�ו��B

};
