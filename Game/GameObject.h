/*!
 *@brief	�Q�[���I�u�W�F�N�g�̊��N���X�B
 */

#pragma once

#define _CGAMEOBJECT_H_

class GameObject
{

public:
	GameObject();
	~GameObject();

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


};

