#pragma once
#include "physics/PhysicsStaticObject.h"

class StageSelectFloor : public GameObject
{
public:
	StageSelectFloor();
	~StageSelectFloor();

	bool Start();
	void Update();

	/// <summary>
	/// ���W���w��B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �X�P�[�����w��B
	/// </summary>
	/// <param name="scale">�X�P�[��</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// ��]���w��B
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

private:

	CVector3 m_position = CVector3::Zero();				//���W�B
	CVector3 m_scale = CVector3::One();					//�X�P�[���B

	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B

	SkinModelRender* m_skinModelRender = nullptr;				//�X�L�����f���B
	SkinModelRender* m_skinModelRenderCollision = nullptr;		//�����蔻��p���f���B

	PhysicsStaticObject m_physicsStaticObject;					//�ÓI�����I�u�W�F�N�g�B

};

