#pragma once
#include "GameObject.h"

class OrderSheet: public GameObject
{
public:
	OrderSheet();
	~OrderSheet();

	bool Start();
	void Update();

	/// <summary>
	/// ���W���w�肷��֐��B
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

	/// <summary>
	/// �X�P�[�����w�肷��֐��B
	/// </summary>	
	/// <param name="scale">�X�P�[��</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ��]���w�肷��֐��B
	/// </summary>
	/// <param name="rotation">��]</param>
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// ���W���擾����B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

private:

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();						//�X�P�[���B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	SpriteRender* m_spriteRenderSheetNo1 = nullptr;			//�摜�����N���X�B��ԉ��̃V�[�g�B
	SpriteRender* m_spriteRenderSheetNo2 = nullptr;			//�摜�����N���X�B��O�̃V�[�g�B

};

