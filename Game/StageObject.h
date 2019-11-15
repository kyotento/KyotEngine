#pragma once
#include "physics/PhysicsStaticObject.h"

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

	/// <summary>
/// ���W�w��B
/// </summary>
/// <param name="a">���W</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
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
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
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
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// ��]�������Ă���B
	/// </summary>
	/// <returns>��]</returns>
	CQuaternion GetRotation()
	{
		return m_rotation;
	}

	/// <summary>
	/// �u������̖̂��O�i�[�B
	/// </summary>
	enum ObjectNames
	{
		enDesk,				//���M�B
		enDelivery,			//�����󂯓n�����B			
		enDishHold,			//���M�u����B
		enDustBox,			//�S�~���B
		enGasStove,			//�R�����B
		enKitchen,			//�M�􂢏�B
		enOnionBox,			//�ʂ˂��{�b�N�X�B			
		enTomatoBox,		//�g�}�g�{�b�N�X�B
		enCuttingDesk		//�܂ȔB
	};

protected:

	SkinModelRender* m_skinModelRender = nullptr;				//��������ł�B
	SkinModelRender* m_skinModelRenderCollidion = nullptr;		//��������ł�(�����蔻��p�{�b�N�X����)�B

	CVector3 m_position = CVector3::Zero();						//���W�B
	CVector3 m_scale = CVector3::One();							//�X�P�[���B

	CQuaternion m_rotation = CQuaternion::Identity();			//��]�B

	PhysicsStaticObject m_physicsStaticObject;					//�ÓI�����I�u�W�F�N�g�B
											
	ObjectNames m_objName = enDesk;								//�I�u�W�F�N�g�̖��O�B

private:





};

