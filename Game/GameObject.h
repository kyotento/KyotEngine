/*!
 *@brief	�Q�[���I�u�W�F�N�g�̊��N���X�B
 */

#pragma once

#define _CGAMEOBJECT_H_

typedef unsigned char GameObjectPriority; //unsigned char�̓��`��B

class GameObject /*:  Noncopy*/
{

public:
	GameObject() :
		m_priority(0),       //�����D��x�O�B
		m_startflag(false),  //false�B
		m_deadflag(false)    //�ŏ��͎���łȂ��B
	{
	}

	virtual ~GameObject();

	//�Ԃ�l����������ƕԂ��B
	virtual bool Start()
	{
		return true;
	}

	//Update�֐��B
	virtual void Update()
	{

	}

protected:

	GameObjectPriority m_priority;    //���s�D��x�B
	 
	bool m_startflag;                 //�X�^�[�g�������ۂ��̃t���O�B
	bool m_deadflag;                  //���S�t���O�B
//	bool m_isRegistDeadList = false;  //�l�͂ˁA���S���X�g�ɐς܂ꂽ�������񂾁B
	bool m_activeflag = true;         //�A�N�e�B�u���ۂ��t���O�B

};

