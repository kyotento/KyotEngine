/// <summary>
/// �`�F�b�N�}�[�N�QD�B
/// </summary>
#pragma once
#include "GameObject.h"

class Check : public GameObject
{
public:
	Check();
	~Check();

	bool Start();
	void Update();

	/// <summary>
	/// ���W���w�肷��B
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

private:

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();						//�g�嗦�B

	SkinModelRender* m_skinModelRender = nullptr;			//�X�L�����f���B

};

