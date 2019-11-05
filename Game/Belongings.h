/// <summary>
/// �H�ו��̊��N���X�B
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


	void SetState(int a)
	{
		if (a == 0)		//������Ă����ԁB
		{
			m_state = enHave;		
		}
		if (a == 1)		//�u����Ă����ԁB
		{
			m_state = enPutting;
		}
		if (a == 2)		//�؂��Ă����ԁB
		{
			m_state = enCutting;
		}
	}

	/// <summary>
	/// ��Ԃ���肷��B
	/// </summary>
	/// <returns>���</returns>
	int GetState()
	{
		return m_state;
	}

	/// <summary>
	/// �H�ו����������B
	/// </summary>
	/// <returns>���Ă�I�u�W�F�N�g���H�ו������������f���邽�߂̒l</returns>
	int GetIndentValue()
	{
		return m_IdentificationValue;
	}


protected:

	/// <summary>
	/// ���Ă�I�u�W�F�N�g���H�ו������������f���邽�߂̒l�B
	/// </summary>
	/// <value>0=�H�ו��A1=�������</value>
	int m_IdentificationValue = 0;			

	/// <summary>	
	/// �H�ו��̏�ԁB
	/// </summary>
	enum state
	{
		enHave,				//������Ă����ԁB
		enPutting,			//�u����Ă����ԁB
		enCutting,			//�؂��Ă����ԁB
	};

	state m_state = enPutting;			//�H�ו��̏�ԁB

private:




};

