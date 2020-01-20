#pragma once
#include "GameObject.h"
#include "StartCountdown.h"
#include "GameOver.h"

class Timer : public GameObject
{
public:
	Timer();
	~Timer();

	bool Start();
	void Update();

	/// <summary>
	/// �������Ԃ�00:00�ƕ\�����邽�߂̌v�Z�����B
	/// </summary>
	void UnitChange();

	/// <summary>
	///	�t�H���g��`�悷�邽�߂̊֐��B
	/// </summary>
	void AfterFontRender();

private:

	int m_second = 0;				//�b�B
	int m_minute = 0;				//���B

	float m_timer = 30.f;			//�^�C�}�[�B
	float m_fontScale = 1.5f;		//�t�H���g�̃X�P�[���B

	CVector2 m_fontPosition = CVector2::Zero();					//�t�H���g�̍��W�B

	CVector3 m_position2D = CVector3::Zero();					//2D�̍��W�B
	CVector3 m_scale2D = CVector3::Zero();						//2D�̃X�P�[���B

	CVector4 m_fontColor = CVector4::Black;					//�t�H���g�̐F�B

	CQuaternion m_quaternion2D = CQuaternion::Identity();		//2D�̉�]�B

	SpriteRender* m_spriteRender = nullptr;			//2D��`�悷�邽�߂̃N���X�B
	FontRender* m_fontRender = nullptr;				//�t�H���g��`�悷�邽�߂̃N���X�B
	StartCountdown* m_startCountDown = nullptr;		//�Q�[���J�n�O�̏����B
	GameOver* m_gameOver = nullptr;			//�Q�[���I���N���X�B

	Font m_font;			//�t�H���g�N���X�B


};

