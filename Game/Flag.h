/// <summary>
/// �X�e�[�W�̊��B
/// </summary>
#pragma once
#include "GameObject.h"

class Flag : public GameObject
{
public:
	Flag();
	~Flag();

	bool Start();
	void Update();

	/// <summary>
	/// �{�^���𐶐�����֐��B
	/// </summary>
	void NewButton();

	/// <summary>
	/// �{�^�������������B
	/// </summary>
	void DeleteButton();
	
	/// <summary>
	/// ���W���w�肷��B
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
	/// �X�P�[�����w�肷��B
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

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_position2D = CVector3::Zero();				//�摜�̍��W�B
	CVector3 m_scale = CVector3::Zero();					//�X�P�[���B
	CVector3 m_scale2D = CVector3::One()*2.f;				//�摜�̃X�P�[���B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	SkinModelRender* m_skinModelRender = nullptr;			//���f�������B
	SkinModelRender* m_skinModelRenderB = nullptr;			//B�{�^���摜�����B


};

