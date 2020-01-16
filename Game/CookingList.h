/// <summary>
/// �����̖��O�̃N���X�B
/// </summary>
#pragma once
#include "GameObject.h"
#include "Belongings.h"
#include "Random.h"

class CookingList : public GameObject
{
public:
	CookingList();
	~CookingList();

	bool Start();
	void Update();

	/// <summary>
	/// �����̏����i�[���Ă���B
	/// </summary>
	void CookingInformations();

	/// <summary>
	/// ������ݒ肷��B
	/// </summary>
	int OrderSetting();

	/// <summary>
	/// �����̖��O���X�g�B
	/// </summary>
	enum cookingList
	{
		enTomatoSoup,		//�g�}�g�X�[�v�B
		enOnionSoup,		//�ʂ˂��X�[�v�B
		encookingListNum	//���������B
	};

	/// <summary>
	/// �쐬���闿���̖��O���擾����B
	/// </summary>
	/// <returns>������</returns>
	cookingList GetCookingList()
	{
		return m_dishName;
	}

	/// <summary>
	/// �����ɕK�v�ȍޗ��̎�ނ̐��B
	/// </summary>
	/// <returns>�����ɕK�v�ȍޗ��̎��</returns>
	int GetFoodType()
	{
		return m_foodtype;
	}

	/// <summary>
	/// �����ɕK�v�ȍޗ��̐����擾����B
	/// </summary>
	/// <returns>�����ɕK�v�ȍޗ��̐�</returns>
	int GetMaterialNum()
	{
		return m_materialNum;
	}

private:

	int m_materialNum = 0;		//�����ɕK�v�ȍޗ��̐��B
	int m_foodtype = 0;			//�����ɕK�v�ȍޗ��̎�ށB

	cookingList m_dishName = encookingListNum;		//�������B

};

