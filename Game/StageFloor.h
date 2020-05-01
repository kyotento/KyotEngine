#pragma once
#include "physics/PhysicsStaticObject.h"

class StageFloor : public GameObject
{
public:
	StageFloor();
	~StageFloor();

	bool Start();
	
	/// <summary>
	/// �X�e�[�W�̏��𐶐����鏈���B
	/// </summary>
	/// <param name="stageNum">�X�e�[�W�ԍ�</param>
	void NewSelectFloor(int stageNum);

	/// <summary>
	/// ���W���w�肷��B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �X�P�[�����w�肷�邌�B
	/// </summary>
	/// <param name="scale">�X�P�[��</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// ��]���w�肷��B
	/// </summary>
	/// <param name="rot">��]�B</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}


private:

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();						//�X�P�[���B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	SkinModelRender* m_skinModelRender = nullptr;			//�������p�X�L�����f���B
	PhysicsStaticObject m_physicsStaticObject;				//�ÓI�����I�u�W�F�N�g�B

};

