#pragma once

class River : public GameObject
{
public:
	River();
	~River();

	bool Start();
	void Update();

	/// <summary>
	/// ���W���擾����B
	/// </summary>
	/// <returns>���W�B</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// ���W���w�肷��B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPositon(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �X�P�[�����w�肷��B
	/// </summary>
	/// <param name="scale">�X�P�[��</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// ��]���w�肷��B
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

private:

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();						//�X�P�[���B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	SkinModelRender* m_skinModelRender = nullptr;			//�X�L�����f���B

};

