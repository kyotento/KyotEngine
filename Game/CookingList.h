/// <summary>
/// �����̖��O�̃N���X�B
/// </summary>
#pragma once
#include "GameObject.h"

class CookingList : public GameObject
{
public:
	CookingList();
	~CookingList();

	/// <summary>
	/// �����̖��O���X�g�B
	/// </summary>
	enum cookingList
	{
		enTomatoSoup,		//�g�}�g�X�[�v�B
		enOnionSoup,		//�ʂ˂��X�[�v�B
		encookingListNum	//���������B
	};

private:

	int m_materialNum = 0;		//�����ɕK�v�ȍޗ��̐��B

	cookingList m_dishName = encookingListNum;		//�������B

};

