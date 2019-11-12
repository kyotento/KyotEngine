/// <summary>
/// ����B
/// </summary>
#pragma once
#include "KitchenWare.h"
#include "SoupBase.h"

class Pot : public KitchenWare
{
public:
	Pot();
	~Pot();

	bool Start();
	void Update();

	/// <summary>
	/// �X�[�v�̕����̏����B
	/// </summary>
	void Soup();

private:

	/// <summary>
	/// ��̏�ԁB
	/// </summary>
	enum PotState
	{
		enZero,			//���������Ă��Ȃ��B
		enOne,			//������������Ă���B
		enTwo,			//�ӂ��Ȃɂ����͂����Ă���B
		enComplete		//���������B
	};


	CVector3 m_soupPos;			//�X�[�v�̍��W�B

	PotState m_potState = enZero;			//��̏�Ԃ��i�[�������́B

	SoupBase* m_soupBase = nullptr;			//�X�[�v�����B

};
