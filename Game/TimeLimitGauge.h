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
	/// �Q�[�W�̏�ԁB
	/// </summary>
	enum GaugeState
	{
		en66Then,		//�U�U���ȏ�̂Ƃ��B	
		en33Then,		//�R�R���ȏ�̂Ƃ��B
		en10Then,		//�P�O���ȏ�̂Ƃ��B
		en10Less		//�P�O�������̂Ƃ��B
	};

private:

	CVector2 m_pivot = { 0.0f,0.5f };				//�s�{�b�g�B

	CVector3 m_position = CVector3::Zero();			//���W�B
	CVector3 m_scale = CVector3::One();				//�X�P�[���B

	GaugeState m_gaugeState = en66Then;				//�Q�[�W�̏�ԁB
	GaugeState m_oldGaugeState = en66Then;			//1�t���[���O�̃Q�[�W�̏�ԁB

	SpriteRender* m_spriteRender = nullptr;			//�摜�`��p�B


};

