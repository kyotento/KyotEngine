#pragma once
#include "character/CharacterController.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

	/// <summary>
	/// �v���C���[�ړ��N���X�B
	/// </summary>
	void Movement();

	/// <summary>
	/// �v���C���[��]�N���X�B
	/// </summary>
	void Rotation();

private:

	float m_moveSpeed = 10.f;								//�ړ����x�B

	CVector3 m_position = CVector3::Zero();					//�v���C���[�̍��W�B
	CVector3 m_characonPos = CVector3::Zero();				//�L�����R���̍��W�B
	CVector3 m_scale = CVector3::One();						//�g�嗦�B
	CVector3 m_move = CVector3::Zero();						//�L�����R���Ƃ��v���C���[�̈ړ����x���v�Z�������́B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	CharacterController m_characon;							//�L�����R���B

	SkinModelRender* m_skinModelRender = nullptr;			//�X�L�����f���B

};

