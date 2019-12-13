#pragma once

class Gauge : public GameObject
{
public:
	Gauge();
	~Gauge();

	bool Start();
	void Update();

	/// <summary>
	/// �Q�[�W���g�傷��B
	/// </summary>
	/// <param name="time">�g�厞��</param>
	void Expansion(float time);

	/// <summary>
	/// �Q�[�W�̊g�又��
	/// </summary>
	/// <param name="time">�g�劮������</param>
	/// <param name="numberOfTimes">�g���</param>
	void Magnification(float time, float numberOfTimes);

	/// <summary>
	/// �Q�[�W��X���g�嗦�B
	/// </summary>
	/// <returns>�g�嗦X��</returns>
	float GetScale()
	{
		return m_x;
	}

	/// <summary>
	/// ���W���擾����B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// ���W���w�肷��B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �Q�[�W�̊g�嗦���ő傩�ǂ�����Ԃ��B
	/// </summary>
	/// <returns>�g��ő�l�t���O</returns>
	bool GetGaugeMax()
	{
		return m_gaugeMax;
	}

	/// <summary>
	/// �Q�[�W�̊g�嗦�𔼕��ɂ���B
	/// </summary>
	void GaugeHalf()
	{
		m_x = m_x / 2;
	}

private:

	bool m_gaugeMax = false;							//�Q�[�W�̊g�嗦���ő�̂Ƃ�true�ɂȂ�B

	float m_x = 0.0f;									//�Q�[�W��X���g�嗦�B
	float m_expansionTimer = 0.f;						//�g�又���Ɏg���^�C�}�[�B

	CVector2 m_pivot = { 0.f,0.5f };					//��_�B

	CVector3 m_position = {0,0,0};						//�Q�[�W�Ɗ�Ղ̍��W�B
	CVector3 m_scaleGauge = CVector3::One();			//�Q�[�W�̊g�嗦�B

	//SpriteRender* m_spriteRender = nullptr;			//�Q�[�W��՗p�X�v���C�g�B
	//SpriteRender* m_spriteRenderGauge = nullptr;		//�Q�[�W�p�X�v���C�g�B

	SkinModelRender* m_skinModelRender = nullptr;				//�Q�[�W��՗p�X�L�����f���B
	SkinModelRender* m_skinModelRenderGauge = nullptr;			//�Q�[�W�p�X�L�����f���B

};

