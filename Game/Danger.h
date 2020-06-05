/// <summary>
/// �댯�}�[�N2D�B
/// </summary>
#pragma once
#include "GameObject.h"

class Danger : public GameObject
{
public:
	Danger();
	~Danger();

	bool Start();
	void Update();

	/// <summary>
	/// ���W���w��B
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

private:

	CVector3 m_position = CVector3::Zero();				//���W�B
	CVector3 m_scale = CVector3::One();

	SkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f���B

};

