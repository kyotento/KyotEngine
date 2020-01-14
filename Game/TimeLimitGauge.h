#pragma once
#include "GameObject.h"

class TimeLimitGauge : public GameObject
{
public:
	TimeLimitGauge();
	~TimeLimitGauge();

	bool Start();
	void Update();

	/// <summary>
	/// ��Ԃ�ύX���鏈���B
	/// </summary>
	void StateChange();

	/// <summary>
	/// ���f����ύX���鏈���B
	/// </summary>
	void ModelChange();

	/// <summary>
	/// �X�P�[���ύX�B
	/// </summary>
	/// 120�b�ŃX�P�[����0�ɂȂ�B
	void ChangeScale();

	/// <summary>
	/// �X�P�[���ύX
	/// </summary>
	/// <param name="time">�k������</param>
	/// �X�P�[����0�ɂȂ鎞�Ԃ�ݒ肵�����ꍇ�g�p����B
	void ChangeScale(float time);

	/// <summary>
	/// ���W��ݒ肷��֐��B
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

	/// <summary>
	/// �g�嗦��ݒ肷��B
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// �g�嗦��ς���X����
	/// </summary>
	/// <param name="scale_x">X���̊g�嗦</param>
	void SetScale(int scale_x)
	{
		m_scale_x = scale_x;
	}

	/// <summary>
	/// X���̊g�嗦���擾����B
	/// </summary>
	/// <returns>�g�嗦X</returns>
	float GetScale_X()
	{
		return m_scale_x;
	}
	
	/// <summary>
	/// �Q�[�W�̏�ԁB
	/// </summary>
	enum GaugeState
	{
		en66Then,		//�U�U���ȏ�̂Ƃ��B	
		en33Then,		//�R�R���ȏ�̂Ƃ��B
		en10Then,		//�P�O���ȏ�̂Ƃ��B
		en10Less		//�P�O�������̂Ƃ��B
	};

	/// <summary>
	/// �Q�[�W�̏�Ԃ��擾����B
	/// </summary>
	/// <returns>�Q�[�W�̏��</returns>
	int GetGaugeState()
	{
		return m_gaugeState;
	}

	/// <summary>
	/// �^�C�����~�b�g�t���O���擾����B
	/// </summary>
	/// <returns>�^�C�����~�b�g�t���O</returns>
	bool GetTimeLimitFlag()
	{
		return m_timeLimitFlag;
	}

private:

	float m_scale_x = 1.f;							//�g�嗦X�B

	bool m_timeLimitFlag = false;					//���Ԑ����𒴂�����true�ɂȂ�B(�g�嗦��0�ɂȂ�����)�B

	CVector2 m_pivot = { 0.0f,0.5f };				//���S�n�B

	CVector3 m_position = CVector3::Zero();			//���W�B
	CVector3 m_scale = CVector3::One();				//�X�P�[���B

	GaugeState m_gaugeState = en66Then;				//�Q�[�W�̏�ԁB
	GaugeState m_oldGaugeState = en66Then;			//1�t���[���O�̃Q�[�W�̏�ԁB

	SpriteRender* m_spriteRender = nullptr;			//�摜�`��p�B

};

