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
	/// �H�ו����I�u�W�F�N�g�̍��W�ɒu�������B
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
	/// �I�u�W�F�N�g�̏�Ԃ�ύX����B
	/// </summary>
	/// <param name="a">���</param>
	void SetState(int a)
	{
		if (a == 0) {
			m_state = en_default;
		}
		if (a == 1) {
			m_state = en_onObject;
		}
	}

	/// <summary>
	/// �I�u�W�F�N�g�̏�Ԃ���������B
	/// </summary>
	/// <returns></returns>
	int GetState()
	{
		return m_state;
	}

protected:

	Belongings* m_belongings = nullptr;
	Gauge* m_gauge = nullptr;

	/// <summary>
	/// �I�u�W�F�N�g�̏�ԁB
	/// </summary>
	enum enState
	{
		en_default,					//��������Ă��Ȃ���ԁB
		en_onObject,				//�����I�u�W�F�N�g������Ă����ԁB

	};

	enState m_state = en_default;

};

