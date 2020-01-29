#pragma once
#include "GameObject.h"

class GameCamera : public GameObject
{
public:
	GameCamera();
	~GameCamera();

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
	/// ���W���擾����B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// ��]���w�肷��B
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// ��]���擾����B
	/// </summary>
	/// <returns>��]</returns>
	CQuaternion GetRotation()
	{
		return m_rotation;
	}

private:

	float m_near = 10.f;									//�ߕ��ʁB
	float m_far = 10000.f;									//�����ʁB

	CVector3 m_position = { 0.0f, 900.0f, -600.0f };		//�J�����̍��W�B
	CVector3 m_target = CVector3::Zero();					//�^�[�Q�b�g�̍��W�B

	CQuaternion m_rotation = CQuaternion::Identity();		//�J�����̉�]�B


};

