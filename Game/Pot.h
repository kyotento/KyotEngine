/// <summary>
/// ����B
/// </summary>
#pragma once
#include "Belongings.h"
#include "SoupBase.h"
#include "Gauge.h"
#include "Check.h"
#include "Danger.h"
#include "Fire.h"

class Pot : public Belongings
{
public:
	Pot();
	~Pot();

	bool Start();
	void Update();

	/// <summary>
	/// ��Ԃ�ω�������B
	/// </summary>
	void StateChange();

	/// <summary>
	/// �X�[�v���������ꂽ���̏���
	/// </summary>
	void Soup();

	/// <summary>
	/// �X�[�v�����������B
	/// </summary>
	void DeleteLikeSoup();

	/// <summary>
	/// �摜�̍��W�X�V�֐��B
	/// </summary>
	void Vector2DUpdate();

	/// <summary>
	/// �댯�}�[�N2D�`�揈���B
	/// </summary>
	void Danger2D();

	/// <summary>
	/// �Ύ��}�[�N2D�`�揈���B
	/// </summary>
	void Fire2D();

	/// <summary>
	/// ���M�ɓ����Ă���H�ו��̎�ނ�ݒ肷��B
	/// </summary>
	/// <param name="FoodType">���M�ɓ����Ă���H�ו�</param>
	void SetPutSoupFoods(int FoodType)
	{
		m_putSoupFoods = FoodType;
	}

	/// <summary>
	/// �Q�[�W�̊g�又���B
	/// �����炪�R�����̏�ɂ��鎞�̂݌Ă΂��B
	/// </summary>
	void PotGaugeExpansion();

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
	float m_dangerStartTimer = 0;	//�댯�}�[�N���o��܂ł̃^�C�}�[�B

	bool m_checkFlag = false;		//�`�F�b�N�}�[�N����������Ă��邩�ǂ����B
	bool m_dangerFlag = false;		//�댯�}�[�N����������Ă��邩�ǂ����B
	bool m_fireFlag = false;		//�Ύ��}�[�N����������Ă���Ƃ��B

	CVector3 m_soupPos = CVector3::Zero();			//�X�[�v�̍��W�B
	CVector3 m_gaugePos = CVector3::Zero();			//�Q�[�W�̍��W�B


	SoupBase* m_soupBase = nullptr;			//�X�[�v�����B
	Gauge* m_gauge = nullptr;				//�Q�[�W�B
	Belongings* m_food = nullptr;			//�H�ו��B
	Check* m_check = nullptr;				//�`�F�b�N�}�[�N�B
	Danger* m_danger = nullptr;				//�댯�}�[�N�B
	Fire* m_fire = nullptr;					//�Ύ��}�[�N�B

};
