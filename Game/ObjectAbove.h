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
	/// ����Ă���I�u�W�F�N�g����������B
	/// </summary>
	/// <param name="">�I�u�W�F�N�g�̃|�C���^�̎Q��</param>
	void TakeThings(Belongings*&);

	/// <summary>
	/// �Q�[�W�̍��W���w�肷��B
	/// </summary>
	/// <param name=""></param>
	void SetGaugePosition(Gauge*);

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

protected:

	Belongings* m_belongings = nullptr;			//�����Ƃ̂ł���I�u�W�F�N�g�B
	Gauge* m_gauge = nullptr;					//�Q�[�W�B

	enState m_state = en_default;		//�I�u�W�F�N�g�̏�ԁB

};

