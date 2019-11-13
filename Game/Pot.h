/// <summary>
/// ����B
/// </summary>
#pragma once
#include "KitchenWare.h"
#include "SoupBase.h"
#include "Gauge.h"

class Pot : public KitchenWare
{
public:
	Pot();
	~Pot();

	bool Start();
	void Update();

	/// <summary>
	/// �X�[�v���������ꂽ�Ƃ��̏����B
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
		enThree,		//�O�����������Ă����ԁB
		enComplete		//���������B���ŏI����Ă���B
	};


	CVector3 m_soupPos = CVector3::Zero();			//�X�[�v�̍��W�B
	CVector3 m_gaugePos = CVector3::Zero();			//�Q�[�W�̍��W�B

	PotState m_potState = enZero;			//��̏�Ԃ��i�[�������́B

	SoupBase* m_soupBase = nullptr;			//�X�[�v�����B
	Gauge* m_gauge = nullptr;				//�Q�[�W�B

};
