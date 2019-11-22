#pragma once
#include "StageObject.h"
#include "Belongings.h"
#include "Gauge.h"
/// <summary>
/// ����u�����Ƃ��ł���I�u�W�F�N�g�̊��N���X�B
/// </summary>

class ObjectAbove : public StageObject
{
public:
	ObjectAbove();
	~ObjectAbove();

	/// <summary>
	/// �����Ă�����̂��I�u�W�F�N�g�̍��W�ɒu�������B
	/// </summary>
	/// <param name="">���Ă����</param>
	void PutThings(Belongings*);

	/// <summary>
	/// �����Ă��鉘�ꂽ���M���w��̍��W�ɒu�������B
	/// </summary>
	/// <param name=""></param>
	void SetDirtyDishPos(Belongings*);

	/// <summary>
	/// ���M���w��̍��W�ɒu�������B(���ꂽ���M)�B
	/// </summary>
	/// <param name="">���Ă����(���M)</param>
	void SetDishPos(Belongings*);

	/// <summary>
	/// ����Ă���I�u�W�F�N�g����������B
	/// </summary>
	/// <param name="">�I�u�W�F�N�g�̃|�C���^�̎Q��</param>
	void TakeThings(Belongings*&);

	/// <summary>
	/// �Q�[�W�̍��W���w�肷��B
	/// </summary>
	/// <param name=""></param>
	void SetGaugePosition(Gauge*);

	///// <summary>
	///// ���M�̐����w�肷��B
	///// </summary>
	///// <param name="dishNum">���M�̐�</param>
	//void SetDishNum(int dishNum)
	//{
	//	m_DishNum = dishNum;
	//}

	///// <summary>
	///// ���M�̐����擾����B
	///// </summary>
	///// <returns>���M�̐�</returns>
	//int GetDishNum()
	//{
	//	return m_DishNum;
	//}

	/// <summary>
	/// �I�u�W�F�N�g�̏�ԁB
	/// </summary>
	enum enState
	{
		en_default,					//��������Ă��Ȃ���ԁB
		en_onObject,				//�����I�u�W�F�N�g������Ă����ԁB
	};

	/// <summary>
	/// �I�u�W�F�N�g�̏�Ԃ�ύX����B
	/// </summary>
	/// <param name="objectAboveState">���</param>
	void SetState(enState objectAboveState)
	{
		m_state = static_cast<enState>(objectAboveState);
	}

	/// <summary>
	/// �I�u�W�F�N�g�̏�Ԃ���������B
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̏��</returns>
	int GetState()
	{
		return m_state;
	}

	/// <summary>
	/// �u������̖̂��O�i�[�B
	/// </summary>
	enum ObjectNames
	{
		enDesk,						//���M�B
		enDelivery,					//�����󂯓n�����B			
		enDishHold,					//���M�u����B
		enDustBox,					//�S�~���B
		enGasStove,					//�R�����B
		enKitchen,					//�M�􂢏�B
		enOnionBox,					//�ʂ˂��{�b�N�X�B			
		enTomatoBox,				//�g�}�g�{�b�N�X�B
		enCuttingDesk,				//�܂ȔB
		enNumberOfObjectAbove		//���Ă镨�̎�ނ̐��B
	};


protected:


	Gauge* m_gauge = nullptr;					//�Q�[�W�B

	enState m_state = en_default;				//�I�u�W�F�N�g�̏�ԁB

	ObjectNames m_objName = enDesk;				//�I�u�W�F�N�g�̖��O�B�����g��Ȃ��B

	Belongings* m_belongings = nullptr;			//�����Ƃ̂ł���I�u�W�F�N�g�B
private:


//	int m_DishNum = 0;			//���M�̐��B

};

