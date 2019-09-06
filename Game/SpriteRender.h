#pragma once
#include "Sprite.h"
#include "graphics/Camera.h"
class SpriteRender : public GameObject
{
public:
	SpriteRender();
	~SpriteRender();

	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="textureFilePath">�e�N�X�`���t�@�C���p�X�B</param>
	/// <param name="w">���B</param>
	/// <param name="h">�������B</param>
	/// <param name="isDraw3D">3D��ԏ�ɕ`�悷�邩�B</param>
	void Init(const wchar_t* textureFilePath, float w, float h, bool isDraw3D = false);
	
	/// <summary>
	/// ���W�ݒ�B
	/// </summary>
	/// <param name="pos">�RD�x�N�g���B</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <returns>���W�B</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// ��]�ݒ�B
	/// </summary>
	/// <param name="rot">��]�B</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// ��]�����擾�B
	/// </summary>
	/// <returns>��]�B</returns>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	/// <summary>
	/// Pivot�̐ݒ�B
	/// </summary>
	/// <param name="pivot">Pivot�B</param>
	void SetPivot(const CVector2& pivot)
	{
		m_pivot = pivot;
	}

	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Render()override;

private:
	Camera::EnUpdateProjMatrixFunc m_projMatrixFunc = Camera::enUpdateProjMatrixFunc_Ortho;

	bool m_Draw3D = false;		//3D��ԏ�ɕ`�悷�邩�B

	float m_w = 0;								//���B
	float m_h = 0;								//�����B

	CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//Pivot�B
	CVector3 m_position;						//���W�B
	CVector3 m_scale = { 1.f,1.f,1.f };			//�X�P�[���B
	CQuaternion m_rotation;						//��]�B

	Sprite m_sprite;					//Sprite�B
	//Camera m_camera;
};

