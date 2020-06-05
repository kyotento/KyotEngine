/// <summary>
/// �Ύ��}�[�N2D�B
/// </summary>
#pragma once
#include "GameObject.h"

class Fire : public GameObject
{
public:
	Fire();
	~Fire();

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

private:

	CVector3 m_position = CVector3::Zero();				//���W�B

	SkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f���B

};

