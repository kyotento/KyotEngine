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
	/// <param name="belongings">�u���Ă������</param>
	void SetSoupBase(Belongings* belongings);

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
		enDish				//���M�B
	};

protected:		

	bool m_CuttingModel = false;			//�؂�ꂽ���f���ɂȂ��Ă��邩�B
														//todo �R���X�g���N�^�ݒ�߂�ǂ��B
	IdentificationValue m_identification = enFood;		//�I�u�W�F�N�g�n���̐ݒ�B(�e�N���X�̃R���X�g���N�^�Őݒ肵�Ă�����K�v������)�B

	state m_foodState = enPutting;			//�H�ו��̏�ԁB

private:




};

