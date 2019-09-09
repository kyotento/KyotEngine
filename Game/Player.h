#pragma once

class Player : public GameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

private:

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();						//�g�嗦�B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	SkinModelRender* m_skinModelRender = nullptr;			//�X�L�����f���B

};

