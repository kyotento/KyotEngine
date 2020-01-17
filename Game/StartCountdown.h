#pragma once
#include "GameObject.h"

class StartCountdown : public GameObject
{
public:
	StartCountdown();
	~StartCountdown();

	bool Start();
	void Update();

	/// <summary>
	/// �X�P�[���̍X�V�����B
	/// </summary>
	void ScaleUpdate();

	/// <summary>
	/// �Q�[����i�s���邩�ۂ������߂�t���O��ύX����֐��B
	/// </summary>
	/// <param name="gameStartFlag">�Q�[���X�V�t���O</param>
	void SetGameStartFlag(bool gameStartFlag)
	{
		m_gameStartFlag = gameStartFlag;
	}

	/// <summary>
	///	�Q�[����U�����邩�ۂ������߂�t���O�̏�Ԃ��擾����֐��B
	/// </summary>
	/// <returns>�Q�[���X�V�t���O</returns>
	bool GetGameStartFlag()
	{
		return m_gameStartFlag;
	}

private:

	float m_scale = 0.f;
	float m_deleteTimer = 0.f;								//�摜�������^�C�}�[�B

	bool m_newReady = false;								//Ready���������ꂽ���B
	bool m_newStart = false;								//Start���������ꂽ���B
	bool m_gameStartFlag = false;							//�X�e�[�W�X�^�[�g�t���O�B

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scaleReady = CVector3::Zero();				//Ready�摜�X�P�[���B
	CVector3 m_scaleStart = CVector3::Zero();				//�X�^�[�g�摜�B

	SpriteRender* m_spriteRenderReady = nullptr;			//Ready�̉摜���o���N���X�B
	SpriteRender* m_spriteRenderStart = nullptr;			//�X�^�[�g�̉摜���o���N���X�B

};

