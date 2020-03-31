#pragma once
#include "GameObject.h"
#include "GameCamera.h"
#include "Flag.h"
#include "StageSelectDetailed.h"

#include "character/CharacterController.h"

class Bus : public GameObject
{
public:
	Bus();
	~Bus();

	bool Start();
	void Update();

	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move();

	/// <summary>
	///	��]�����B
	/// </summary>
	void Rotation();

	/// <summary>
	/// �J������Ǐ]�����鏈���B
	/// </summary>
	void FollowCamera();

	/// <summary>
	/// �����������鏈���B
	/// </summary>
	void FlagSearch();

	/// <summary>
	/// ���W���w�肷��B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
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
	/// ��]���w�肷��B
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

private:

	static const int FLAG_NUM = 3;							//���̐��B

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One()*5.f;					//�X�P�[���B
	CVector3 m_stickPower = CVector3::Zero();				//���X�e�B�b�N�̌X�����ێ����邽�߂̂��́B
	CVector3 m_move = CVector3::Zero();						//�L�����R���̈ړ����x���v�Z�������́B(��������)�B
	CVector3 m_resetPosition = CVector3::Zero();			//�o�X�̃��Z�b�g���W�B

	CQuaternion m_rotation = CQuaternion::Identity();		//��]�B

	SkinModelRender* m_skinModelRender = nullptr;			//�X�L�����f���B
	GameCamera* m_gameCamera = nullptr;						//�J�����B

	Flag* m_flag[FLAG_NUM] = { nullptr };					//���B
	StageSelectDetailed* m_stageSelectDetailed = nullptr;	//�X�e�[�W�̏ڍ׉摜�B

	CharacterController m_characon;			//�L�����R���B

};

