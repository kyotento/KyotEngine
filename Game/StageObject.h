#pragma once

/// <summary>
///�X�e�[�W��ɒu�����I�u�W�F�N�g�̊��N���X�B 
/// </summary>

class StageObject : public GameObject
{
public:
	StageObject();
	~StageObject();

	bool Start();
	void Update();


protected:

	/// <summary>
	/// ���W�w��B
	/// </summary>
	/// <param name="a">���W</param>
	void SetPosition(CVector3 a)
	{
		m_position = a;
	}

	/// <summary>
	/// ���W�������Ă���B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// �X�P�[���w��B
	/// </summary>
	/// <param name="a">�X�P�[��</param>
	void SetScale(CVector3 a)
	{
		m_scale = a;
	}

	/// <summary>
	/// �X�P�[���������Ă���B
	/// </summary>
	/// <returns></returns>
	CVector3 GetScale()
	{
		return m_scale;
	}

	/// <summary>
	/// ��]���w�肷��B
	/// </summary>
	/// <param name="a">��]</param>
	void SetRotation(CQuaternion a)
	{
		m_rotation = a;
	}

	/// <summary>
	/// ��]�������Ă���B
	/// </summary>
	/// <returns>��]</returns>
	CQuaternion GetRotation()
	{
		return m_rotation;
	}

	SkinModelRender* m_skinModelRender = nullptr;				//��������ł�B

private:

	CVector3 m_position = CVector3::Zero();						//���W�B
	CVector3 m_scale = CVector3::One();							//�X�P�[���B

	CQuaternion m_rotation = CQuaternion::Identity();			//��]�B



};

