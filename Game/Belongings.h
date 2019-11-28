/// <summary>
/// ���Ă���̂̊��N���X�B
/// </summary>
#pragma once
#include "StageObject.h"

class Belongings : public StageObject
{
public:

	Belongings();
	~Belongings();

	bool Start();
	void Update();

	/// <summary>
	/// ��Ԃ���肷��B
	/// </summary>
	/// <returns>���</returns>
	int GetFoodState()
	{
		return m_foodState;
	}

	/// <summary>
	/// �H�ו����������B
	/// </summary>
	/// <returns>���Ă�I�u�W�F�N�g���H�ו������������f���邽�߂̒l</returns>
	int GetIndentValue()
	{
		return m_identification;
	}

	/// <summary>
	/// �X�[�v���ۂ��I�u�W�F�N�g�𐶐�����B
	/// </summary>
	/// <param name="belongings">�u���Ă��鎝�Ă����</param>
	void SetSoupBase(Belongings* belongings);

	/// <summary>
	/// �X�[�v�����������B
	/// </summary>
	/// <param name="belongings">�u���Ă��鎝�Ă����</param>
	void DeleteSoup(Belongings* belongings);

	/// <summary>
	///	���M�ɐH�ו���u�������B
	/// </summary>
	/// <param name="belongings">���Ă����</param>
	void PutDishs(Belongings* belongings);

	/// <summary>
	/// ���M�􂢏�̏d�˂Ă��邨�M���炨�M����Ƃ鏈���B
	/// </summary>
	/// <param name="belongings">���Ă����(���M)</param>
	void PutDishFromKitchen(Belongings* belongings);

	/// <summary>	
	/// �H�ו��̏�ԁB
	/// </summary>
	enum state
	{
		enHave,				//������Ă����ԁB
		enPutting,			//�u����Ă����ԁB
		enCutting,			//�؂��Ă����ԁB
	};

	/// <summary>
	/// �H�ו��̏�Ԃ��Z�b�g����B
	/// </summary>
	/// <param name="foodsState">�H�ו��̏��</param>
	void SetState(state foodsState)
	{
		m_foodState = static_cast<state>(foodsState);
	}

	/// <summary>
	/// �I�u�W�F�N�g���ǂ̌n���ɑ����邩�B
	/// </summary>
	enum IdentificationValue
	{
		enFood,				//�H�ו��B
		enKitchenWare,		//�������B
		enDish,				//���M�B
		enDirtyDish			//���ꂽ���M�B
	};

	/// <summary>
	/// ����̏�ԁB
	/// </summary>
	enum PotState
	{
		enZero,			//���������Ă��Ȃ��B
		enOne,			//������������Ă���B
		enTwo,			//�ӂ��Ȃɂ����͂����Ă���B
		enThree,		//�O�����������Ă����ԁB
		enComplete		//���������B���ŏI����Ă���B
	};

	/// <summary>
	/// ����̏�Ԃ��擾����B
	/// </summary>
	/// <returns>����̏��</returns>
	int GetPotState()
	{
		return m_potState;
	}


protected:		

	bool m_CuttingModel = false;			//�؂�ꂽ���f���ɂȂ��Ă��邩�B
														//todo �R���X�g���N�^�ݒ�߂�ǂ��B
	IdentificationValue m_identification = enFood;		//�I�u�W�F�N�g�n���̐ݒ�B(�e�N���X�̃R���X�g���N�^�Őݒ肵�Ă�����K�v������)�B

	state m_foodState = enPutting;			//�H�ו��̏�ԁB

	PotState m_potState = enZero;			//��̏�Ԃ��i�[�������́B

private:




};

